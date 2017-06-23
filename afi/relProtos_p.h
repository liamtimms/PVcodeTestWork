/*
 *******************************************************************
 *
 * $Source: /bscl/CvsTree/bscl/gen/config/proto.head,v $
 *
 * Copyright (c) 1995
 * BRUKER ANALYTISCHE MESSTECHNIK GMBH
 * D-76287 Rheinstetten, Germany
 *
 * All Rights Reserved
 *
 *
 * $State: Exp $
 *
 *******************************************************************
 */

#ifndef _P_
#	if defined(HAS_PROTO) || defined(__STDC__) || defined(__cplusplus)
#		define _P_(s) s
#	else
#		define _P_(s) ()
#	endif
#endif

/* /opt/PV5.1/prog/parx/src/afi/initMeth.c */
void initMeth _P_((void));
/* /opt/PV5.1/prog/parx/src/afi/loadMeth.c */
void loadMeth _P_((const char *));
/* /opt/PV5.1/prog/parx/src/afi/backbone.c */
void backbone _P_((void));
void UpdateEchoTime _P_((void));
void UpdateTR1 _P_((void));
void UpdateTR2 _P_((void));
void UpdatetotalTR _P_((void));
void UpdateGeometryMinima _P_((double *, double *, double *, double *));
void UpdateGradients _P_((double, double));
void UpdateFrequencyOffsets _P_((void));
void InplaneGeometryRel _P_((void));
void SliceGeometryRel _P_((void));
YesNo UpdateRFPulses _P_((YesNo, char *));
void HandleParameterVisibility _P_((int));
/* /opt/PV5.1/prog/parx/src/afi/parsRelations.c */
void afi_TR1Range _P_((void));
void afi_TR1Rel _P_((void));
void afi_TR2Range _P_((void));
void afi_TR2Rel _P_((void));
void afi_total_TRRange _P_((void));
void afi_total_TRRel _P_((void));
void AveragesRange _P_((void));
void AveragesRel _P_((void));
void EchoTimeRange _P_((void));
void EchoTimeRel _P_((void));
void ExcPulseAngleRelation _P_((void));
void EffSWhRange _P_((void));
void EffSWhRel _P_((void));
void EncGradDurRange _P_((void));
void EncGradDurRel _P_((void));
void EchoPositionRange _P_((void));
void EchoPositionRel _P_((void));
void ReadSpoilGradRange _P_((void));
void ReadSpoilGradRel _P_((void));
void ReadSpoilGradDurRange _P_((void));
void ReadSpoilGradDurRel _P_((void));
void ExcPulseEnumRel _P_((void));
void ExcPulseRange _P_((void));
void ExcPulseRel _P_((void));
void DeriveGainsRange _P_((void));
void DeriveGainsRel _P_((void));
void NDummyScansRel _P_((void));
void NDummyScansRange _P_((void));
void ShowAllParsRange _P_((void));
void ShowAllParsRel _P_((void));
void Local_RFSpoilingRelation _P_((void));
/* /opt/PV5.1/prog/parx/src/afi/BaseLevelRelations.c */
void SetBaseLevelParam _P_((void));
void SetBasicParameters _P_((void));
void SetFrequencyParameters _P_((void));
void SetGradientParameters _P_((void));
void SetPpgParameters _P_((void));
void SetInfoParameters _P_((void));
void SetMachineParameters _P_((void));
void PrintTimingInfo _P_((void));
/* /opt/PV5.1/prog/parx/src/afi/RecoRelations.c */
void SetRecoParam _P_((void));
int PowerOfTwo _P_((int));
