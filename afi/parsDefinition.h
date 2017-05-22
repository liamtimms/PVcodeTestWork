/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/gre/parsDefinition.h,v $
 *
 * Copyright (c) 2007
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: parsDefinition.h,v 1.1.6.1 2007/04/25 06:13:44 mawi Exp $
 *
 * ***************************************************************/

/****************************************************************/
/* INCLUDE FILES						*/
/****************************************************************/

/* =============================================================
 * Definition of local method parameters. Parameters that are
 * not editable and calculated inside the methods backbone such
 * as gradient values will have the backbone routine as default
 * relations. Only parameters that appear editable in the method
 * editor need a specific parameter relation and range checking
 * function.
 * ============================================================*/

/* -------------------------------------------------------
 * Frequency encoding parameter 
 * ------------------------------------------------------*/

double parameter
{
  display_name "Read Dephase Gradient";
  format "%f";
  units  "%";
  relations backbone;
}ReadDephGrad;

double parameter
{
  display_name "Max Read Dephase Gradient";
  format "%f";
  units  "%";
  relations backbone;
}ReadDephGradLim;

double parameter
{
  display_name "Read Gradient";
  format "%f";
  units "%";
  relations backbone;
}ReadGrad;

double parameter
{
  display_name "Max Read Gradient";
  format "%f";
  units "%";
  relations backbone;
}ReadGradLim;

double parameter
{
  display_name "Echo Position";
  format "%f";
  units "%";
  relations EchoPositionRel;
}EchoPosition;

double parameter
{
  display_name "Read Spoiler";
  units "%";
  format "%f";
  relations ReadSpoilGradRel;
}ReadSpoilGrad;

double parameter
{
  display_name "Read Spoiler Duration";
  units "ms";
  format "%f";
  relations ReadSpoilGradDurRel;
}ReadSpoilGradDur;


/* ----------------------------------------------------------
 * Phase encoding parametes
 * ---------------------------------------------------------*/

double parameter
{
  display_name "2D Phase Gradient";
  format "%f";
  units "%";
  relations backbone;
}Phase2DGrad;

double parameter
{
  display_name "Max. 2D Phase Gradient";
  format "%f";
  units "%";
  relations backbone;
}Phase2DGradLim;


double parameter
{
  display_name "3D Phase Gradient";
  format "%f";
  units "%";
  relations backbone;
}Phase3DGrad;

double parameter
{
  display_name "Max. 3D Phase Gradient";
  format "%f";
  units "%";
  relations backbone;
}Phase3DGradLim;


/* ---------------------------------------------------------------
 * Slice selection parameter
 * --------------------------------------------------------------*/

double parameter
{
  display_name "Exc. Slice Gradient";
  format "%f";
  units  "%";
  relations backbone;
}ExcSliceGrad;


double parameter
{
  display_name "Max. Exc. Slice Gradient";
  format "%f";
  units  "%";
  relations backbone;
}ExcSliceGradLim;


double parameter
{
  display_name "Exc. Slice Reph. Gradient";
  format "%f";
  units  "%";
  relations backbone;
}ExcSliceRephGrad;

double parameter
{
  display_name "Max. Exc. Slice Reph. Gradient";
  format "%f";
  units  "%";
  relations backbone;
}ExcSliceRephGradLim;



/* ----------------------------------------------------------
 * Definition of RF Pulse parameters 
 * ---------------------------------------------------------*/


PV_PULSE_LIST parameter
{
  display_name "Excitation Pulse Choice";
  relations    ExcPulseEnumRel;
}ExcPulseEnum;


PVM_RF_PULSE_TYPE parameter
{
  display_name "Excitation Pulse";
  relations    ExcPulseRel;
}ExcPulse;


/* ---------------------------------------------------------
 * remaining local method parameters
 * --------------------------------------------------------*/

YesNo parameter
{
  display_name "Show Noneditable Pars";
  relations ShowAllParsRel;
}ShowAllPars;

double parameter
{
  display_name "Encoding Gradient Duration";
  relations EncGradDurRel;
  units "ms";
  format "%.3f";
}EncGradDur;

int parameter 
{
  display_name "Number of dummy scans";
  relations NDummyScansRel;
} NDummyScans;

/*--------------------------------------------------------------
*AFI parameters
*---------------------------------------------------------------*/

double parameter
{
  display_name "AFI TR1";
  relations afi_TR1Rel;
  units "ms";
  format "%.3f";
}afi_TR1;

double parameter
{
  display_name "AFI TR2";
  relations afi_TR2Rel;
  units "ms";
  format "%.3f";
}afi_TR2;

double parameter
{
  display_name "AFI total TR";
  relations afi_total_TRRel;
  units "ms";
  format "%.3f";
}afi_total_TR;

OnOff parameter
{
  display_name  "RF Spoiler ";
  relations backbone;
}RFSpoilerOnOff;
 
double parameter RFSpoilerlist[];

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/


