/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/demo/gre/parsLayout.h,v $
 *
 * Copyright (c) 2007
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: parsLayout.h,v 1.4 2013/09/20 08:50:27 sako Exp $
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
  ExcPulse1;
} RF_Pulses;

parclass
{
  NDummyScans;
  EncGradDur;
  PVM_EffSWh;
  PVM_AcquisitionTime;
  PVM_EchoPosition;
  ReadGrad;
  ReadDephGrad;
  ReadSpoilGradDur;
  ReadSpoilGrad;
  Phase2DGrad;
  Phase3DGrad;
  ExcSliceGrad;		 	 
  ExcSliceRephGrad; 
  DigitizerPars;
}SequenceDetails;

parclass
{
  Method;
  PVM_EchoTime;
  PVM_MinEchoTime;
  PVM_RepetitionTime;
  PVM_NAverages;
  PVM_ScanTimeStr;
  PVM_ScanTime;
  PVM_DeriveGains;
  RF_Pulses;
  Nuclei;
  SequenceDetails;
  Encoding;
  ImageGeometry;
} MethodClass;


/* ***************************************************************/
/*	E N D   O F   F I L E					 */
/* ***************************************************************/

