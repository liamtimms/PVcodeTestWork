/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/gre/parsLayout.h,v $
 *
 * Copyright (c) 2007
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: parsLayout.h,v 1.3.2.1 2007/04/25 06:13:44 mawi Exp $
 *
 * ***************************************************************/

/* ***************************************************************/
/*	PARAMETER CLASS	               			       	 */
/* ***************************************************************/

/*--------------------------------------------------------------*
 * Definition of the PV class...
 *--------------------------------------------------------------*/

parclass
{
  PVM_EffSWh;
  PVM_AcquisitionTime;
  EchoPosition;
  ReadGrad;
  ReadGradLim;
  ReadDephGrad;
  ReadDephGradLim;
  ReadSpoilGradDur;
  ReadSpoilGrad;
}FrequencyEncoding;

parclass
{
  Phase2DGrad;
  Phase2DGradLim;
}Phase2DEncoding;

parclass
{
  Phase3DGrad;
  Phase3DGradLim;
}Phase3DEncoding;

parclass
{
  ExcSliceGrad;		 
  ExcSliceGradLim;	 
  ExcSliceRephGrad;	 
  ExcSliceRephGradLim;	 
}SliceSelection;

parclass
{
  ExcPulseEnum;
  ExcPulse;
  RFSpoilerOnOff;
} RF_Pulses;

parclass
{
  NDummyScans;
  ShowAllPars;
  EncGradDur;
  FrequencyEncoding;
  Phase2DEncoding;
  Phase3DEncoding;
  SliceSelection;
  DigitizerPars;
}SequenceDetails;

parclass
{
  Method;
  PVM_EchoTime;
  PVM_MinEchoTime;
  afi_TR1;
  afi_TR2;
  afi_total_TR;
  PVM_NAverages;
  PVM_ScanTimeStr;
  PVM_DeriveGains;
  RF_Pulses;
  Nuclei;
  SequenceDetails;
  Encoding;
  StandardInplaneGeometry;
  StandardSliceGeometry;
} MethodClass;


/* ***************************************************************/
/*	E N D   O F   F I L E					 */
/* ***************************************************************/

