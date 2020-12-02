/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "asn/nr-rrc-15.6.0.asn1"
 * 	`asn1c -fcompound-names -pdu=all -findirect-choice -fno-include-deps -gen-PER -no-gen-OER -no-gen-example -D rrc`
 */

#ifndef	_RRC_RF_ParametersMRDC_H_
#define	_RRC_RF_ParametersMRDC_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RRC_RF_ParametersMRDC__ext1__srs_SwitchingTimeRequested {
	RRC_RF_ParametersMRDC__ext1__srs_SwitchingTimeRequested_true	= 0
} e_RRC_RF_ParametersMRDC__ext1__srs_SwitchingTimeRequested;

/* Forward declarations */
struct RRC_BandCombinationList;
struct RRC_FreqBandList;
struct RRC_BandCombinationList_v1540;
struct RRC_BandCombinationList_v1550;
struct RRC_BandCombinationList_v1560;

/* RRC_RF-ParametersMRDC */
typedef struct RRC_RF_ParametersMRDC {
	struct RRC_BandCombinationList	*supportedBandCombinationList;	/* OPTIONAL */
	struct RRC_FreqBandList	*appliedFreqBandListFilter;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	struct RRC_RF_ParametersMRDC__ext1 {
		long	*srs_SwitchingTimeRequested;	/* OPTIONAL */
		struct RRC_BandCombinationList_v1540	*supportedBandCombinationList_v1540;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext1;
	struct RRC_RF_ParametersMRDC__ext2 {
		struct RRC_BandCombinationList_v1550	*supportedBandCombinationList_v1550;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext2;
	struct RRC_RF_ParametersMRDC__ext3 {
		struct RRC_BandCombinationList_v1560	*supportedBandCombinationList_v1560;	/* OPTIONAL */
		struct RRC_BandCombinationList	*supportedBandCombinationListNEDC_Only;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext3;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRC_RF_ParametersMRDC_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_RRC_srs_SwitchingTimeRequested_6;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_RRC_RF_ParametersMRDC;
extern asn_SEQUENCE_specifics_t asn_SPC_RRC_RF_ParametersMRDC_specs_1;
extern asn_TYPE_member_t asn_MBR_RRC_RF_ParametersMRDC_1[5];

#ifdef __cplusplus
}
#endif

#endif	/* _RRC_RF_ParametersMRDC_H_ */
#include <asn_internal.h>