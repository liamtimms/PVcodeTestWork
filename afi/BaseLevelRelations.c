/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/gre/BaseLevelRelations.c,v $
 *
 * Copyright (c) 2007-2009
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: BaseLevelRelations.c,v 1.7.2.5 2009/09/10 08:38:27 mawi Exp $
 *
 * ***************************************************************/

static const char resid[] = "$Id: BaseLevelRelations.c,v 1.7.2.5 2009/09/10 08:38:27 mawi Exp $ (c) 2009 Bruker BioSpin MRI GmbH";


#define DEBUG		     1
#define DB_MODULE	   0
#define DB_LINE_NR	 0




#include "method.h"

void SetBaseLevelParam()
{

  DB_MSG(("-->SetBaseLevelParam"));

  SetBasicParameters();
  
  
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBaseLevelParam: Error in function call!");
    return;
  }
  
  SetFrequencyParameters();
  
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBaseLevelParam: In function call!");
    return;
  }
  
  SetPpgParameters();

  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBaseLevelParam: In function call!");
    return;
  }
  
  SetGradientParameters();
  
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBaseLevelParam: In function call!");
    return;
  }
  
  SetInfoParameters();
  
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBaseLevelParam: In function call!");
    return;
  }
  
  
  SetMachineParameters();
  
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBaseLevelParam: In function call!");
    return;
  }
  
  PrintTimingInfo();

  DB_MSG(("<--SetBaseLevelParam"));
  

}

void SetBasicParameters( void )
{
  int spatDim, specDim;
  int nSlices;


  DB_MSG(("-->SetBasicParameters"));
    
  /* ACQ_dim */

  spatDim = PTB_GetSpatDim();
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBasicParameters: In function call!");
    return;
  }
  
  specDim = PTB_GetSpecDim();
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBasicParameters: In function call!");
    return;
    }
  
  ACQ_dim = spatDim + specDim;
  ParxRelsParRelations("ACQ_dim",Yes);
  
  /* ACQ_dim_desc */
  
  ATB_SetAcqDimDesc( specDim, spatDim, NULL );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBasicParameters: In function call!");
    return;
  }
  
  /* ACQ_size */
  
  ATB_SetAcqSize( Spatial, spatDim, PVM_EncMatrix, NULL, No );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBasicParameters: In function call!");
    return;
  }
  
  /* NSLICES */
  
  nSlices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBasicParameters: In function call!");
    return;
  }
  
  ATB_SetNSlices( nSlices );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBasicParameters: In function call!");
    return;
  }
  
  /* NR */
  
  ATB_SetNR( PVM_NRepetitions );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBasicParameters: In function call!");
    return;
  }
  

    /* NI */
  
  ATB_SetNI( nSlices*2 );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBasicParameters: In function call!");
    return;
  }
  
  
  /* AVERAGING */


  switch(PVM_MotionSupOnOff)
  {
    default:
    case Off:
      ATB_SetNA( PVM_NAverages );
      if( PVM_ErrorDetected == Yes )
      {
        UT_ReportError("SetBasicParameters: In function call!");
        return;
      }
      ATB_SetNAE( 1 );
      if( PVM_ErrorDetected == Yes )
      {
        UT_ReportError("SetBasicParameters: In function call!");
        return;
      }
      break;
    case On:
      ATB_SetNAE( PVM_NAverages );
      if( PVM_ErrorDetected == Yes )
      {
        UT_ReportError("SetBasicParameters: In function call!");
        return;
      }
      ATB_SetNA( 1 );
      if( PVM_ErrorDetected == Yes )
      {
        UT_ReportError("SetBasicParameters: In function call!");
        return;
      }
      break;
  }
 
  
  /* ACQ_ns */
  
  ACQ_ns_list_size = 2;
  ParxRelsParRelations("ACQ_ns_list_size",Yes);

  ACQ_ns_list[0] = 1;

  
  NS = ACQ_ns = ACQ_ns_list[0];
  
  
  
  /* NECHOES */
  
  NECHOES = 2;
  
  /* ACQ_obj_order */
  
  PARX_change_dims("ACQ_obj_order",NI);
  
  ATB_SetAcqObjOrder( nSlices, PVM_ObjOrderList, 2, 1 );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBasicParameters: In function call!");
    return;
  }
  
  
  /* DS */
  
  DS =NDummyScans ;
  ACQ_DS_enabled = Yes;
  
  
  ATB_DisableAcqUserFilter();
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBasicParameters: In function call!");
    return;
  }

  ATB_SetAcqScanSize( One_scan );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetBasicParameters: In function call!");
    return;
  }
  
  
  DB_MSG(("<--SetBasicParameters"));
}

void SetFrequencyParameters( void )
{
  int nslices, dim, i;

  DB_MSG(("-->SetFrequencyParameters"));


  ATB_SetNuc1(PVM_Nucleus1);
   
  sprintf(NUC2,"off");
  sprintf(NUC3,"off");
  sprintf(NUC4,"off");
  sprintf(NUC5,"off");
  sprintf(NUC6,"off");
  sprintf(NUC7,"off");
  sprintf(NUC8,"off");
  
  ATB_SetNucleus(PVM_Nucleus1);
  
  
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetFrequencyParameters: In function call!");
    return;
  }
  
  
  /* setting of AQ_mod DSPFIRM SW_h                              */

  ATB_SetDigPars();
    
  ACQ_O1_mode = BF_plus_Offset_list;
  ParxRelsParRelations("ACQ_O1_mode",Yes);
  

  /* RF Spoiling */
 
  dim = PARX_get_dim("RFSpoilerlist",1);
  ACQ_O2_list_size = dim;
  ACQ_O2_mode = BF_plus_Offset_list;
  ParxRelsParRelations("ACQ_O2_mode",Yes);
  PARX_change_dims("ACQ_O2_list",dim);
  for(i=0;i<dim;i++)
  ACQ_O2_list[i] = RFSpoilerlist[i];
  
  ACQ_O3_mode = BF_plus_Offset_list;
  ParxRelsParRelations("ACQ_O3_mode",Yes);
  
  O1 = 0.0;
  O2 = 0.0;
  O3 = 0.0;
  O4 = 0.0;
  O5 = 0.0;
  O6 = 0.0;
  O7 = 0.0;
  O8 = 0.0;
  
  nslices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetFrequencyParameters: In function call!");
    return;
  }
  
  ATB_SetAcqO1List( nslices,
                    PVM_ObjOrderList,
                    PVM_SliceOffsetHz );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetFrequencyParameters: In function call!");
    return;
  }
  
  ATB_SetAcqO1BList( nslices,
                     PVM_ObjOrderList,
                     PVM_ReadOffsetHz);
 
  ATB_SetRouting();
  
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetFrequencyParameters: In function call!");
    return;
  }
  
  DB_MSG(("<--SetFrequencyParameters"));
}


void SetGradientParameters( void )
{
  int spatDim;

  DB_MSG(("-->SetGradientParameters"));
  
  ATB_SetAcqPhaseFactor( 1 );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetGradientParameters: In function call!");
    return;
  }
  
  spatDim = PTB_GetSpatDim();
  PARX_change_dims("ACQ_phase_encoding_mode", spatDim );
  PARX_change_dims("ACQ_phase_enc_start", spatDim );

  switch(spatDim)
    {
    case 3:
      ACQ_phase_encoding_mode[2] = User_Defined_Encoding;
      ACQ_phase_enc_start[2]     = -1; /* set but not used     */
      ACQ_spatial_size_2 = PVM_EncMatrix[2];
      ParxRelsCopyPar("ACQ_spatial_phase_2","PVM_EncValues2");
      /* no break, falls through                               */
    case 2:
      ACQ_phase_encoding_mode[1] = User_Defined_Encoding;
      ACQ_phase_enc_start[1]     = -1; /* set but not used     */
      ACQ_spatial_size_1 = PVM_EncMatrix[1];
      ParxRelsCopyPar("ACQ_spatial_phase_1","PVM_EncValues1");
      /* no break, falls through                               */
    case 1:
    default:
      ACQ_phase_encoding_mode[0] = Read;
      ACQ_phase_enc_start[0]     = -1;
      break;
  }

  
  ATB_SetAcqGradMatrix( PVM_NSPacks, 
                        PVM_SPackArrNSlices,
                        PtrType3x3 PVM_SPackArrGradOrient[0],
                        PVM_ObjOrderList );
  
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetGradientParameters: In function call!");
    return;
  }
  
  ACQ_scaling_read  = 1.0;
  ACQ_scaling_phase = 1.0;
  ACQ_scaling_slice = 1.0;
  
  ACQ_rare_factor = 1;
  
  ACQ_grad_str_X = 0.0;
  ACQ_grad_str_Y = 0.0;
  ACQ_grad_str_Z = 0.0;
  
  strcpy(GRDPROG, "");
  
  ATB_SetAcqTrims( 9,
                   ExcSliceGrad,                    /* t0 */             
                   -ExcSliceRephGrad,               /* t1 */
                   -ReadDephGrad,                   /* t2 */
                   Phase2DGrad,                     /* t3 */
                   -Phase3DGrad,                    /* t4 */
                   ReadGrad,                        /* t5 */
                   -Phase2DGrad,                    /* t6 */
                   Phase3DGrad,                     /* t7 */
                   ReadSpoilGrad                    /* t8 */
  );

  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetGradientParameters: In function call!");
    return;
  }
  
  DB_MSG(("<--SetGradientParameters"));

}

void SetPpgParameters(void)
{
  double riseT,igwT;
  int slices;
  DB_MSG(("-->SetPpgParameters"));
  
  if( ParxRelsParHasValue("ACQ_trigger_enable") == No )
  {
    ACQ_trigger_enable = No;
  }
  
  if( ParxRelsParHasValue("ACQ_trigger_reference") == No )
  {
    ACQ_trigger_reference[0] = '\0';
  }
  
  if( ParxRelsParHasValue("ACQ_trigger_delay") == No )
  {
    ACQ_trigger_delay = 0;
  }
  
  ParxRelsParRelations("ACQ_trigger_reference",Yes);
  
  
  ACQ_vd_list_size=1;
  PARX_change_dims("ACQ_vd_list",1);
  ACQ_vd_list[0] = 1e-6;
  ParxRelsParRelations("ACQ_vd_list",Yes);
  
  ACQ_vp_list_size=1;
  PARX_change_dims("ACQ_vp_list",1);
  ACQ_vp_list[0] = 1e-6;
  ParxRelsParRelations("ACQ_vp_list",Yes);
  
  if(Yes==ATB_SetMultiRec())
  {
    ATB_SetPulprog("afi.4ch");
  }
  else
  {
    ATB_SetPulprog("afi.ppg");
  }

  L[0] = ACQ_size[1];


  if( PTB_GetSpatDim() == 3)
  {
    L[1] = ACQ_size[2];
  }
  else
  {
    L[1] = 1;
  }

  slices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );
  igwT   = CFG_InterGradientWaitTime();
  riseT  = CFG_GradientRiseTime();

  D[0]  = (afi_TR1 - PVM_MinRepetitionTime 
            + igwT + 0.04)/1000.0;
  D[10]  = (afi_TR2 - PVM_MinRepetitionTime 
            + igwT + 0.04)/1000.0;
  D[1]  = riseT/1000.0;
  D[2]  = CFG_AmplifierEnable()/1000.0;
  D[3]  = (EncGradDur - riseT) / 1000.0;
  D[5]  = (PVM_EchoTime - PVM_MinEchoTime + riseT + igwT)/1000.0;
  D[4]  = riseT/1000.0;
  D[6]  = (ReadSpoilGradDur - EncGradDur)/1000.0;
  D[7]  = riseT/1000.0;
  
  /* set shaped pulses     */
  sprintf(TPQQ[0].name,ExcPulse.Filename);
  if(PVM_DeriveGains == Yes)
  {
    TPQQ[0].power  = ExcPulse.Attenuation;
  }
  TPQQ[0].offset = 0.0;
    
  ParxRelsParRelations("TPQQ",Yes);
  
  /* set duration of pulses          */
  P[0] = ExcPulse.Length * 1000;
  ParxRelsParRelations("P",Yes);

  DB_MSG(("<--SetPpgParameters"));
}

void SetInfoParameters( void )
{
  int slices, i, spatDim;
  
  DB_MSG(("-->SetInfoParameters"));
  
  spatDim = PTB_GetSpatDim();
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetInfoParameters: In function call!");
    return;
  }
  
  ATB_SetAcqMethod();

  ATB_SetAcqFov( Spatial, spatDim, PVM_Fov, PVM_AntiAlias );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetInfoParameters: In function call!");
    return;
  }
  
  ACQ_flip_angle = PVM_ExcPulseAngle;
  
  PARX_change_dims("ACQ_echo_time",1);

  ACQ_echo_time[0] = PVM_EchoTime;
  
  PARX_change_dims("ACQ_inter_echo_time",1);
  ACQ_inter_echo_time[0] = PVM_EchoTime;
  
  PARX_change_dims("ACQ_repetition_time",1);
  ACQ_repetition_time[0] = afi_total_TR;
  
  PARX_change_dims("ACQ_recov_time",1);
  ACQ_recov_time[0] =  
    PVM_RepetitionTime - 
    (PVM_EchoTime/2 + ExcPulse.Length/2);
  
  PARX_change_dims("ACQ_inversion_time",1);
  ACQ_inversion_time[0] = PVM_InversionTime;
  
  ATB_SetAcqSliceAngle( PtrType3x3 PVM_SPackArrGradOrient[0],
			PVM_NSPacks );
  
  ACQ_slice_orient = Arbitrary_Oblique;
  
  ACQ_slice_thick = PVM_SliceThick;
  
  slices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );
  if( PVM_ErrorDetected == Yes )
  {
    UT_ReportError("SetInfoParameters: In function call!");
    return;
  }
  
  PARX_change_dims("ACQ_slice_offset",slices);
  PARX_change_dims("ACQ_read_offset",slices);
  PARX_change_dims("ACQ_phase1_offset",slices);
  PARX_change_dims("ACQ_phase2_offset",slices);
  
  for(i=0;i<slices;i++)
  {
    ACQ_slice_offset[i]  = PVM_SliceOffset[i];
    ACQ_read_offset[i]   = PVM_ReadOffset[i];
    ACQ_phase1_offset[i] = PVM_Phase1Offset[i];
    ACQ_phase2_offset[i] = PVM_Phase2Offset[i];
  }
  
  ACQ_read_ext = (int)PVM_AntiAlias[0];
  
  PARX_change_dims("ACQ_slice_sepn", slices==1 ? 1 : slices-1);
  
  if( slices == 1 )
  {
    ACQ_slice_sepn[0] = 0.0;
  }
  else
  {
    for( i=1; i<slices;i++ )
    {
      ACQ_slice_sepn[i-1]=PVM_SliceOffset[i]-PVM_SliceOffset[i-1];
    }
  }
  
  ATB_SetAcqSliceSepn( PVM_SPackArrSliceDistance,
                       PVM_NSPacks );
  
  
  
  ATB_SetAcqPatientPosition();
  
  ATB_SetAcqExpType( Imaging );
  
  ACQ_n_t1_points = 1;
    
  if( ParxRelsParHasValue("ACQ_contrast_agent") == No )
  {
    ACQ_contrast_agent[0] = '\0';
  }
  
  if( ParxRelsParHasValue("ACQ_contrast") == No )
  {
    ACQ_contrast.volume = 0.0;
    ACQ_contrast.dose = 0.0;
    ACQ_contrast.route[0] = '\0';
    ACQ_contrast.start_time[0] = '\0';
    ACQ_contrast.stop_time[0] = '\0';
  }
  
  ParxRelsParRelations("ACQ_contrast_agent",Yes);
  
  ACQ_position_X = 0.0;
  ACQ_position_Y = 0.0;
  ACQ_position_Z = 0.0;

  PARX_change_dims("ACQ_temporal_delay",1);
  ACQ_temporal_delay[0] = 0.0;
  
  ACQ_RF_power = 0;
  
  ACQ_flipback = No;

  ACQ_n_echo_images = 2;
  
  // initialize ACQ_n_echo_images ACQ_echo_descr
  //            ACQ_n_movie_frames ACQ_movie_descr
  ATB_ResetEchoDescr();
  ATB_ResetMovieDescr();
  
  DB_MSG(("<--SetInfoParameters"));
  
}

void SetMachineParameters( void )
{
  DB_MSG(("-->SetMachineParameters"));

  
  if( ParxRelsParHasValue("ACQ_word_size") == No )
  {
    ACQ_word_size = _32_BIT;
  }
  
  DEOSC = (PVM_AcquisitionTime +ReadSpoilGradDur)*1000.0;
  ACQ_scan_shift = -1;
  ParxRelsParRelations("ACQ_scan_shift",Yes);
  
  DE = DE < 6.0 ? 6.0: DE;
  
  
  PAPS = QP;
  
  ACQ_BF_enable = Yes;
  
  DB_MSG(("<--SetMachineParameters"));
}


void PrintTimingInfo(void)
{
  double te1,te2,tr;

  DB_MSG(("-->PrintTimingInfo"));

  te1=(P[0])/2000.0+(D[3]+D[5])*1000.0;

  te2=D[4]*1000.0 +
      PVM_AcquisitionTime*EchoPosition/100.0;



  tr = ((te1+te2+P[0]/2000.0 + 0.011 + 
	(D[0]+D[1]+D[2]+D[3]+D[6]+D[7])*1000
	+ PVM_AcquisitionTime*(100.0-EchoPosition)/100.0) +
        (te1+te2+P[0]/2000.0 + 0.011 + 
	(D[10]+D[1]+D[2]+D[3]+D[6]+D[7])*1000
	+ PVM_AcquisitionTime*(100.0-EchoPosition)/100.0))
    *NSLICES;
  

  DB_MSG(("te1: %f te2: %f TE : %f should be: %f diff %f\n",
	  te1,te2,te1+te2,PVM_EchoTime,
	  te1+te2-PVM_EchoTime));

  DB_MSG(("tr: %f  should be: %f  diff %f\n",tr,afi_total_TR,
	  tr-afi_total_TR));

  DB_MSG(("<--PrintTimingInfo"));  
}
