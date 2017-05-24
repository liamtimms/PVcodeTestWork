/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/demo/gre/BaseLevelRelations.c,v $
 *
 * Copyright (c) 2007-2011
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: BaseLevelRelations.c,v 1.3 2013/09/06 12:38:38 sako Exp $
 *
 * ***************************************************************/

static const char resid[] = "$Id: BaseLevelRelations.c,v 1.3 2013/09/06 12:38:38 sako Exp $ (c) 2007-2011 Bruker BioSpin MRI GmbH";


#define DEBUG		 0
#define DB_MODULE	 0
#define DB_LINE_NR	 0




#include "method.h"

void SetBaseLevelParam()
{

  DB_MSG(("-->SetBaseLevelParam"));

  SetBasicParameters();
  
  SetFrequencyParameters();
  
  SetPpgParameters();
  
  SetGradientParameters();
  
  SetInfoParameters();
  
  SetMachineParameters();
  
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
 
  specDim = PTB_GetSpecDim();
 
  ACQ_dim = spatDim + specDim;
  ParxRelsParRelations("ACQ_dim",Yes);
  
  /* ACQ_dim_desc */
  
  ATB_SetAcqDimDesc( specDim, spatDim, NULL );

  
  /* ACQ_size */
  
  ATB_SetAcqSize( Spatial, spatDim, PVM_EncMatrix, NULL, No );

  
  /* NSLICES */
  
  nSlices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices ); 
  ATB_SetNSlices( nSlices );

  
  /* NR */
  
  ATB_SetNR( PVM_NRepetitions );

  
  /* NI */
  
  ATB_SetNI( nSlices);
  
  
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
  
  ACQ_ns_list_size = 2; //changed to 2 from 1 for afi
  ParxRelsParRelations("ACQ_ns_list_size",Yes);

  ACQ_ns_list[0] = 1;
 
  NS = ACQ_ns = ACQ_ns_list[0];
   
  
  /* NECHOES */
  
  NECHOES = 2; //changed to 2 from 1 for afi
  
  
  /* ACQ_obj_order */
  
  PARX_change_dims("ACQ_obj_order",NI);
  
  ATB_SetAcqObjOrder( nSlices, PVM_ObjOrderList, 2, 1 );
 
  
  /* DS */
  
  DS =NDummyScans ;
  ACQ_DS_enabled = Yes;
  
  
  ATB_DisableAcqUserFilter();


  ATB_SetAcqScanSize( One_scan );

  
  DB_MSG(("<--SetBasicParameters"));
}

void SetFrequencyParameters( void )
{
  int nslices;
  int dim, i; //added these based on afi

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
  
  
  /* setting of AQ_mod DSPFIRM SW_h                              */

  ATB_SetDigPars();
    
  ACQ_O1_mode = BF_plus_Offset_list;
  ParxRelsParRelations("ACQ_O1_mode",Yes);
  
  ACQ_O2_mode = BF_plus_Offset_list;
  ParxRelsParRelations("ACQ_O2_mode",Yes);
  
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
  
  /* Set BF's to working freuncies on used channels */
  ACQ_BF_enable = No;
  BF1 = PVM_FrqWork[0];
  BF2 = PVM_FrqWork[1];
  /* call relations of BF1 (no need for other BF's) */
  ParxRelsParRelations("BF1", Yes); 


  nslices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );
 
  
  ATB_SetAcqO1List( nslices,
                    PVM_ObjOrderList,
                    PVM_SliceOffsetHz );
 
  
  ATB_SetAcqO1BList( nslices,
                     PVM_ObjOrderList,
                     PVM_ReadOffsetHz);
 
  DB_MSG(("<--SetFrequencyParameters"));
}


void SetGradientParameters( void )
{
  int spatDim;

  DB_MSG(("-->SetGradientParameters"));
  
  ATB_SetAcqPhaseFactor( 1 );

  
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
  
 
  
  ACQ_scaling_read  = 1.0;
  ACQ_scaling_phase = 1.0;
  ACQ_scaling_slice = 1.0;
  
  ACQ_rare_factor = 1;
  
  ACQ_grad_str_X = 0.0;
  ACQ_grad_str_Y = 0.0;
  ACQ_grad_str_Z = 0.0;
  
  strcpy(GRDPROG, "");
  
  /* gradient amplitudes */
  ACQ_gradient_amplitude[0] =  ExcSliceGrad;
  ACQ_gradient_amplitude[1] = -ExcSliceRephGrad;
  ACQ_gradient_amplitude[2] = -ReadDephGrad;
  ACQ_gradient_amplitude[3] =  Phase2DGrad;
  ACQ_gradient_amplitude[4] = -Phase3DGrad;
  ACQ_gradient_amplitude[5] =  ReadGrad;
  ACQ_gradient_amplitude[6] = -Phase2DGrad;
  ACQ_gradient_amplitude[7] =  Phase3DGrad;
  ACQ_gradient_amplitude[8] =  ReadSpoilGrad;
  
  
  DB_MSG(("<--SetGradientParameters"));

}

void SetPpgParameters(void)
{
  double riseT,igwT;
  int slices;
  DB_MSG(("-->SetPpgParameters"));
  
  ACQ_vd_list_size=1;
  PARX_change_dims("ACQ_vd_list",1);
  ACQ_vd_list[0] = 1e-6;
  ParxRelsParRelations("ACQ_vd_list",Yes);
  
  ACQ_vp_list_size=1;
  PARX_change_dims("ACQ_vp_list",1);
  ACQ_vp_list[0] = 1e-6;
  ParxRelsParRelations("ACQ_vp_list",Yes);
  
  ATB_SetPulprog("test_gre.ppg"); //this has a major change in the AFI

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

  //D[0]  = ((PVM_RepetitionTime - PVM_MinRepetitionTime)/slices 
  //          + igwT + 0.01)/1000.0;  
  D[0]  = ((PVM_TR1 - PVM_MinRepetitionTime)/slices 
            + igwT + 0.01)/1000.0;
  D[10]  = ((PVM_TR2 - PVM_MinRepetitionTime)/slices 
            + igwT + 0.01)/1000.0;
            
            
  D[1]  = riseT/1000.0;
  D[2]  = CFG_AmplifierEnable()/1000.0;
  D[3]  = (EncGradDur - riseT) / 1000.0;
  D[5]  = (PVM_EchoTime - PVM_MinEchoTime + riseT + igwT)/1000.0;
  D[4]  = riseT/1000.0;
  D[6]  = (ReadSpoilGradDur - EncGradDur)/1000.0;
  D[7]  = riseT/1000.0;
  
  /* set shaped pulses:
     in this method ACQ_RfShapes[0] is used           
     the pulse duration is stored in baselevel parameter P[0]
  */
  ATB_SetRFPulse("ExcPulse1","ACQ_RfShapes[0]","P[0]");
  

  DB_MSG(("<--SetPpgParameters"));
}

void SetInfoParameters( void )
{
  int slices, i, spatDim;
  
  DB_MSG(("-->SetInfoParameters"));
  
  spatDim = PTB_GetSpatDim();
 
  
  ATB_SetAcqMethod();

  ATB_SetAcqFov( Spatial, spatDim, PVM_Fov, PVM_AntiAlias );
  
  ACQ_flip_angle = ExcPulse1.Flipangle;
  
  PARX_change_dims("ACQ_echo_time",1);

  ACQ_echo_time[0] = PVM_EchoTime;
  
  PARX_change_dims("ACQ_inter_echo_time",1);
  ACQ_inter_echo_time[0] = PVM_EchoTime;
  
  PARX_change_dims("ACQ_repetition_time",1);
  //ACQ_repetition_time[0] = PVM_RepetitionTime;
  ACQ_repetition_time[0] = Afi_total_TR;
  
  PARX_change_dims("ACQ_recov_time",1);
  ACQ_recov_time[0] =  
    PVM_RepetitionTime - 
    (PVM_EchoTime/2 + ExcPulse1.Length/2);
  
  PARX_change_dims("ACQ_inversion_time",1);
  ACQ_inversion_time[0] = PVM_InversionTime;
  
  ATB_SetAcqSliceAngle( PtrType3x3 PVM_SPackArrGradOrient[0],
			PVM_NSPacks );
  
  ACQ_slice_orient = Arbitrary_Oblique;
  
  ACQ_slice_thick = PVM_SliceThick;
  
  slices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );
  
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
  
  ACQ_n_echo_images = 2; //added for AFI
  
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
  
  /* ACQ_experiment _mode and ACQ_ReceiverSelect: */
  
  ATB_SetMultiRec(); //AFI has "ACQ_BF_enable = Yes;" instead of this

  DB_MSG(("<--SetMachineParameters"));
}


void PrintTimingInfo(void)
{
  double te1,te2,tr;

  DB_MSG(("-->PrintTimingInfo"));

  te1=(P[0])/2000.0+(D[3]+D[5])*1000.0;

  te2=D[4]*1000.0 +
      PVM_AcquisitionTime*PVM_EchoPosition/100.0;



  tr = ((te1+te2+P[0]/2000.0 + 0.011 + 
	(D[0]+D[1]+D[2]+D[3]+D[6]+D[7])*1000
	+ PVM_AcquisitionTime*(100.0-PVM_EchoPosition)/100.0) + //first pulse (I think)
	    (te1+te2+P[0]/2000.0 + 0.011 +
	(D[10]+D[1]+D[2]+D[3]+D[6]+D[7])*1000
	+ PVM_AcquisitionTime*(100.0-PVM_EchoPosition)/100.0)) //second pulse 
    *NSLICES;
  

  DB_MSG(("te1: %f te2: %f TE : %f should be: %f diff %f\n",
	  te1,te2,te1+te2,PVM_EchoTime,
	  te1+te2-PVM_EchoTime));

  DB_MSG(("tr: %f  should be: %f  diff %f\n",tr,Afi_total_TR,
	  tr-Afi_total_TR));

  DB_MSG(("<--PrintTimingInfo"));  
}
