//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR, Havelsan.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "gnb_ngap_task.hpp"
#include "gnb_ngap_utils.hpp"

#include <ASN_NGAP_AMFName.h>
#include <ASN_NGAP_BroadcastPLMNItem.h>
#include <ASN_NGAP_GlobalGNB-ID.h>
#include <ASN_NGAP_InitiatingMessage.h>
#include <ASN_NGAP_NGAP-PDU.h>
#include <ASN_NGAP_NGSetupRequest.h>
#include <ASN_NGAP_ProtocolIE-Field.h>
#include <ASN_NGAP_ServedGUAMIItem.h>
#include <ASN_NGAP_SliceSupportItem.h>
#include <ASN_NGAP_SupportedTAItem.h>

namespace nr::gnb
{

void NgapTask::sendNgSetupRequest(int amfId)
{
    auto *amf = findAmfContext(amfId);
    if (amf == nullptr)
        return;

    amf->state = EAmfState::WAITING_NG_SETUP;

    // TODO: this procedure also re-initialises the NGAP UE-related contexts (if any)
    //  and erases all related signalling connections in the two nodes like an NG Reset procedure would do.
    //  More on 38.413 8.7.1.1

    auto *globalGnbId = asn::New<ASN_NGAP_GlobalGNB_ID>();
    globalGnbId->gNB_ID.present = ASN_NGAP_GNB_ID_PR_gNB_ID;
    asn::SetBitString(globalGnbId->gNB_ID.choice.gNB_ID, octet4{config->gnbId});
    asn::SetOctetString(globalGnbId->pLMNIdentity, config->plmn.toOctet3());

    auto *ieGlobalGnbId = asn::New<ASN_NGAP_NGSetupRequestIEs>();
    ieGlobalGnbId->id = ASN_NGAP_ProtocolIE_ID_id_GlobalRANNodeID;
    ieGlobalGnbId->criticality = ASN_NGAP_Criticality_reject;
    ieGlobalGnbId->value.present = ASN_NGAP_NGSetupRequestIEs__value_PR_GlobalRANNodeID;
    ieGlobalGnbId->value.choice.GlobalRANNodeID.present = ASN_NGAP_GlobalRANNodeID_PR_globalGNB_ID;
    ieGlobalGnbId->value.choice.GlobalRANNodeID.choice.globalGNB_ID = globalGnbId;

    auto *ieRanNodeName = asn::New<ASN_NGAP_NGSetupRequestIEs>();
    ieRanNodeName->id = ASN_NGAP_ProtocolIE_ID_id_RANNodeName;
    ieRanNodeName->criticality = ASN_NGAP_Criticality_ignore;
    ieRanNodeName->value.present = ASN_NGAP_NGSetupRequestIEs__value_PR_RANNodeName;
    asn::SetPrintableString(ieRanNodeName->value.choice.RANNodeName, config->name);

    auto *broadcastPlmn = asn::New<ASN_NGAP_BroadcastPLMNItem>();
    asn::SetOctetString(broadcastPlmn->pLMNIdentity, config->plmn.toOctet3());
    for (auto &nssai : config->nssais)
    {
        auto *item = asn::New<ASN_NGAP_SliceSupportItem>();
        asn::SetOctetString(item->s_NSSAI.sST, static_cast<uint8_t>(nssai.sst));
        if (nssai.sd.has_value())
        {
            item->s_NSSAI.sD = asn::New<ASN_NGAP_SD_t>();
            asn::SetOctetString(*item->s_NSSAI.sD, octet3{nssai.sd.value()});
        }
        asn::SequenceAdd(broadcastPlmn->tAISliceSupportList, item);
    }

    auto *supportedTa = asn::New<ASN_NGAP_SupportedTAItem>();
    asn::SetOctetString(supportedTa->tAC, octet3{config->tac});
    asn::SequenceAdd(supportedTa->broadcastPLMNList, broadcastPlmn);

    auto *ieSupportedTaList = asn::New<ASN_NGAP_NGSetupRequestIEs>();
    ieSupportedTaList->id = ASN_NGAP_ProtocolIE_ID_id_SupportedTAList;
    ieSupportedTaList->criticality = ASN_NGAP_Criticality_reject;
    ieSupportedTaList->value.present = ASN_NGAP_NGSetupRequestIEs__value_PR_SupportedTAList;
    asn::SequenceAdd(ieSupportedTaList->value.choice.SupportedTAList, supportedTa);

    auto *iePagingDrx = asn::New<ASN_NGAP_NGSetupRequestIEs>();
    iePagingDrx->id = ASN_NGAP_ProtocolIE_ID_id_PagingDRX;
    iePagingDrx->criticality = ASN_NGAP_Criticality_ignore;
    iePagingDrx->value.present = ASN_NGAP_NGSetupRequestIEs__value_PR_PagingDRX;
    iePagingDrx->value.choice.PagingDRX = ngap_utils::PagingDrxToAsn(config->pagingDrx);

    auto *pdu = asn::ngap::NewMessagePdu<ASN_NGAP_NGSetupRequest>(
        {ieGlobalGnbId, ieRanNodeName, ieSupportedTaList, iePagingDrx});

    sendNgapNonUe(amfId, pdu);
}

void NgapTask::receiveNgSetupResponse(int amfId, ASN_NGAP_NGSetupResponse *msg)
{
    auto *amf = findAmfContext(amfId);
    if (amf == nullptr)
        return;

    auto *ie = asn::ngap::GetProtocolIe(msg, ASN_NGAP_ProtocolIE_ID_id_AMFName);
    if (ie)
        amf->amfName = asn::GetPrintableString(ie->value.choice.AMFName);

    ie = asn::ngap::GetProtocolIe(msg, ASN_NGAP_ProtocolIE_ID_id_RelativeAMFCapacity);
    if (ie)
        amf->relativeCapacity = ie->value.choice.RelativeAMFCapacity;

    ie = asn::ngap::GetProtocolIe(msg, ASN_NGAP_ProtocolIE_ID_id_ServedGUAMIList);
    if (ie)
    {
        for (auto &item : amf->servedGuamiList)
            delete item;
        amf->servedGuamiList.clear();

        auto &list = ie->value.choice.ServedGUAMIList.list;
        for (int i = 0; i < list.count; i++)
        {
            auto servedGuami = new ServedGuami();

            auto &item = list.array[i];
            if (item->backupAMFName)
                servedGuami->backupAmfName = asn::GetPrintableString(*item->backupAMFName);

            ngap_utils::SetGuamiFromAsn(item->gUAMI, servedGuami->guami);
            amf->servedGuamiList.push_back(servedGuami);
        }
    }

    ie = asn::ngap::GetProtocolIe(msg, ASN_NGAP_ProtocolIE_ID_id_PLMNSupportList);
    if (ie)
    {
        // TODO
    }
}

} // namespace nr::gnb