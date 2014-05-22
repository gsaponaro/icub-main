// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/* 
 * Copyright (C) 2010 RobotCub Consortium, European Commission FP6 Project IST-004370
 * Author: Francesco Nori
 * email:  francesco.nori@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/


#include "include/guiControl.h"
#include "include/partMover.h"
#include <stdlib.h>

//*********************************************************************************
void guiControl::destroy_main (GtkWindow *window,    gpointer   user_data)
{
  gtk_widget_destroy (GTK_WIDGET(window));
  window = NULL;
  pos_winPid = NULL;
  gtk_main_quit ();
}

//*********************************************************************************
// This callback exits from the Pid dialog
void guiControl::destroy_win (GtkButton *button, GtkWindow *window)
{
  gtk_widget_destroy (GTK_WIDGET(window));
  window = NULL;
  pos_winPid = NULL;
  gtk_main_quit ();
}

//*********************************************************************************
void guiControl::displayPidValue(int k, GtkWidget *inv,GtkWidget *entry, int posX, int posY, const char *label)
{
  char buffer[40];
  GtkWidget *frame = gtk_frame_new (label);

  gtk_fixed_put    (GTK_FIXED(inv), frame, posX+0, posY);
  gtk_fixed_put    (GTK_FIXED(inv), entry, posX+30, posY+20);
  gtk_widget_set_size_request     (frame, 120, 60);
  gtk_widget_set_size_request     (entry, 50, 20);

  gtk_editable_set_editable ((GtkEditable*) entry, FALSE);
  sprintf(buffer, "%d", k);
  gtk_entry_set_text((GtkEntry*) entry,  buffer);
  return;
}

//*********************************************************************************
void guiControl::changePidValue(int k, GtkWidget *inv,GtkWidget *entry, int posX, int posY, const char * label)
{
  char buffer[40];
  GtkWidget *frame = gtk_frame_new (label);

  gtk_fixed_put    (GTK_FIXED(inv), frame, posX+20, posY);
  gtk_fixed_put    (GTK_FIXED(inv), entry, posX+50, posY+20);
  gtk_widget_set_size_request     (frame, 120, 60);
  gtk_widget_set_size_request     (entry, 50, 20);
  gtk_editable_set_editable ((GtkEditable*) entry, TRUE);
  sprintf(buffer, "%d", k);
  gtk_entry_set_text((GtkEntry*) entry,  buffer);
  return;
}

static void guiControl::radio_click_idl(GtkWidget* radio , gtkClassData* currentClassData)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio)))
    {
        fprintf(stderr, "joint: %d in IDLE mode!\n", *joint);
/*        fprintf(stderr, "(DEBUG: not using iCntrl interface\n", *joint);
        ipid->disablePid(*joint);
        iamp->disableAmp(*joint);
*/
        icntrl2->setControlMode(*joint, VOCAB_CM_IDLE);
    }
    else
    {
    }
}
static void guiControl::radio_click_open(GtkWidget* radio , gtkClassData* currentClassData)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio)))
    {
        fprintf(stderr, "joint: %d in OPENLOOP mode!\n", *joint);
        icntrl2->setOpenLoopMode(*joint);
    }
    else
    {
    }
}
static void guiControl::radio_click_pos(GtkWidget* radio , gtkClassData* currentClassData)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio)))
    {
        fprintf(stderr, "joint: %d in POSITION mode!\n", *joint);
        icntrl2->setPositionMode(*joint);
    }
    else
    {
    }
}

static void guiControl::radio_click_pos_direct(GtkWidget* radio , gtkClassData* currentClassData)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio)))
    {
        fprintf(stderr, "joint: %d in POSITION DIRECT mode!\n", *joint);
        if(icntrl2)
        	icntrl2->setControlMode(*joint, VOCAB_CM_POSITION_DIRECT);
    }
    else
    {
    }
}

static void guiControl::radio_click_mode_mixed(GtkWidget* radio , gtkClassData* currentClassData)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio)))
    {
        fprintf(stderr, "joint: %d in MIXED mode!\n", *joint);
        if(icntrl2)
        	icntrl2->setControlMode(*joint, VOCAB_CM_MIXED);
    }
    else
    {
    }
}

static void guiControl::radio_click_vel(GtkWidget* radio , gtkClassData* currentClassData)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio)))
    {
        fprintf(stderr, "joint: %d in VELOCITY mode!\n", *joint);
        icntrl2->setVelocityMode(*joint);
    }
    else
    {
    }
}
static void guiControl::radio_click_trq(GtkWidget* radio , gtkClassData* currentClassData)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio)))
    {
        fprintf(stderr, "joint: %d in TORQUE mode!\n", *joint);
        icntrl2->setTorqueMode(*joint);
    }
    else
    {
    }
}
static void guiControl::radio_click_imp_pos(GtkWidget* radio , gtkClassData* currentClassData)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio)))
    {
        fprintf(stderr, "WARN: Using old interface! joint: %d in IMPEDANCE POSITION mode!\n", *joint);
        icntrl->setImpedancePositionMode(*joint);
    }
    else
    {
    }
}

static void guiControl::radio_click_imp_vel(GtkWidget* radio , gtkClassData* currentClassData)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio)))
    {
        fprintf(stderr, "WARN: Using old interface! joint: %d in IMPEDANCE VELOCITY mode!\n", *joint);
        icntrl->setImpedanceVelocityMode(*joint);
    }
    else
    {
    }
}

static void guiControl::radio_click_stiff(GtkWidget* radio , gtkClassData* currentClassData)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio)))
    {
        fprintf(stderr, "joint: %d in STIFF mode!\n", *joint);
        iinteract->setInteractionMode(*joint, (yarp::dev::InteractionModeEnum) VOCAB_IM_STIFF);
    }
    else
    {
    }
}

static void guiControl::radio_click_compl(GtkWidget* radio , gtkClassData* currentClassData)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio)))
    {
        fprintf(stderr, "joint: %d in COMPLIANT mode!\n", *joint);
        iinteract->setInteractionMode(*joint, (yarp::dev::InteractionModeEnum) VOCAB_IM_COMPLIANT);
    }
    else
    {
    }
}

//*********************************************************************************
void guiControl::update_menu(int control_mode, int interaction_mode)
{
 switch (control_mode)
  {
      case MODE_IDLE:
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_mode_idl),true);
      break;
      case VOCAB_CM_POSITION:
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_mode_pos),true);
      break;
     /* case VOCAB_CM_POSITION_DIRECT:
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_mode_pos_direct),true);
      break;
      case VOCAB_CM_MIXED:
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_mode_mixed),true);
      break;*/
        case VOCAB_CM_VELOCITY:
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_mode_vel),true);
      break;
      case VOCAB_CM_TORQUE:
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_mode_trq),true);
      break;
      case VOCAB_CM_IMPEDANCE_POS:
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_mode_imp_pos),true);
      break;
      case VOCAB_CM_IMPEDANCE_VEL:
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_mode_imp_vel),true);
      break;

      default:
      case VOCAB_CM_UNKNOWN:
        //NOTE: Unknown!!!
        printf("WARNING: get dealing with unknown control mode\n");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_mode_idl),true);
      break;
  }

 switch (interaction_mode)
  {
      case VOCAB_IM_STIFF:
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_interaction_stiff),true);
      break;
      case VOCAB_IM_COMPLIANT:
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_interaction_compl),true);
      break;

      default:
      case VOCAB_CM_UNKNOWN:
        //NOTE: Unknown!!!
        printf("WARNING: get dealing with unknown interaction mode\n");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radiobutton_interaction_stiff),true);
      break;
  }
}

//*********************************************************************************
void guiControl::guiControl(void *button, void* data)
{
  if (pos_winPid != NULL) 
  {
      gtk_window_set_keep_above    (GTK_WINDOW(pos_winPid),true);
      return;
  }

  gtkClassData* currentClassData = (gtkClassData*) data;
  partMover *currentPart = currentClassData->partPointer;
  joint  = currentClassData->indexPointer;
  icntrl = currentPart->get_IControlMode();
  icntrl2 = currentPart->get_IControlMode2();
  iinteract = currentPart->get_IInteractionMode();
  ipid = currentPart->get_IPidControl();
  iamp = currentPart->get_IAmplifierControl();

  //GtkWidget *winPid = NULL;
  GtkWidget *inv    = NULL;

  //adding a popup window
  pos_winPid = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  char title[255];
  sprintf(title,"Control mode JNT:%d",*joint);
  gtk_window_set_title (GTK_WINDOW (pos_winPid), title);
  
  //adding a set of display
  inv = gtk_fixed_new ();
  gtk_container_add (GTK_CONTAINER (pos_winPid), inv);
  
  label_title = gtk_label_new (title);
  sprintf(title,"Interaction mode JNT:%d",*joint);
  label_title2 = gtk_label_new (title);

  radiobutton_mode_idl  = gtk_radio_button_new_with_label  (NULL, "idle");
  radiobutton_mode_pos  = gtk_radio_button_new_with_label_from_widget         (GTK_RADIO_BUTTON (radiobutton_mode_idl), "position");
  radiobutton_mode_vel  = gtk_radio_button_new_with_label_from_widget         (GTK_RADIO_BUTTON (radiobutton_mode_idl), "velocity");
  radiobutton_mode_trq  = gtk_radio_button_new_with_label_from_widget         (GTK_RADIO_BUTTON (radiobutton_mode_idl), "torque");
  radiobutton_mode_imp_pos  = gtk_radio_button_new_with_label_from_widget     (GTK_RADIO_BUTTON (radiobutton_mode_idl), "impedance position");
  radiobutton_mode_imp_vel  = gtk_radio_button_new_with_label_from_widget     (GTK_RADIO_BUTTON (radiobutton_mode_idl), "impedance velocity");
  radiobutton_mode_open = gtk_radio_button_new_with_label_from_widget         (GTK_RADIO_BUTTON (radiobutton_mode_idl), "openloop");
  radiobutton_mode_pos_direct  = gtk_radio_button_new_with_label_from_widget  (GTK_RADIO_BUTTON (radiobutton_mode_idl), "position direct");
  radiobutton_mode_mixed  = gtk_radio_button_new_with_label_from_widget       (GTK_RADIO_BUTTON (radiobutton_mode_idl), "mixed");

  radiobutton_interaction_stiff  = gtk_radio_button_new_with_label  (NULL, "stiff mode");
  radiobutton_interaction_compl  = gtk_radio_button_new_with_label_from_widget  (GTK_RADIO_BUTTON (radiobutton_interaction_stiff), "compliant mode");

  gtk_fixed_put    (GTK_FIXED(inv), label_title,                  10, 10    );
  gtk_fixed_put    (GTK_FIXED(inv), radiobutton_mode_idl,         10, 30    );
  gtk_fixed_put    (GTK_FIXED(inv), radiobutton_mode_pos,         10, 50    );
  gtk_fixed_put    (GTK_FIXED(inv), radiobutton_mode_pos_direct,  10, 70    );
  gtk_fixed_put    (GTK_FIXED(inv), radiobutton_mode_mixed,       10, 90    );
  gtk_fixed_put    (GTK_FIXED(inv), radiobutton_mode_vel,         10, 110   );
  gtk_fixed_put    (GTK_FIXED(inv), radiobutton_mode_trq,         10, 130   );
  gtk_fixed_put    (GTK_FIXED(inv), radiobutton_mode_imp_pos,     10, 150   );
  gtk_fixed_put    (GTK_FIXED(inv), radiobutton_mode_imp_vel,     10, 170   );
  gtk_fixed_put    (GTK_FIXED(inv), radiobutton_mode_open,        10, 190   );

  gtk_fixed_put    (GTK_FIXED(inv), label_title2,                 10, 210   );
  gtk_fixed_put    (GTK_FIXED(inv), radiobutton_interaction_stiff,10, 230   );
  gtk_fixed_put    (GTK_FIXED(inv), radiobutton_interaction_compl,10, 250   );

  int control_mode=VOCAB_CM_UNKNOWN;
  yarp::dev::InteractionModeEnum interaction_mode=VOCAB_IM_UNKNOWN;
  bool ret = true;
  ret &= icntrl2->getControlMode(*joint, &control_mode);
  ret &= iinteract->getInteractionMode(*joint, &interaction_mode);
  update_menu(control_mode, interaction_mode);
 
  //Rememeber: these signal_connect MUST be placed after the update_menu!
  g_signal_connect (radiobutton_mode_idl,  "clicked",G_CALLBACK (radio_click_idl), &radiobutton_mode_idl);
  g_signal_connect (radiobutton_mode_pos,  "clicked",G_CALLBACK (radio_click_pos), &radiobutton_mode_pos);
  g_signal_connect (radiobutton_mode_pos_direct,  "clicked",G_CALLBACK (radio_click_pos_direct), &radiobutton_mode_pos_direct);
  g_signal_connect (radiobutton_mode_mixed,  "clicked",G_CALLBACK (radio_click_mode_mixed), &radiobutton_mode_mixed);
  g_signal_connect (radiobutton_mode_vel,  "clicked",G_CALLBACK (radio_click_vel), &radiobutton_mode_vel);
  g_signal_connect (radiobutton_mode_trq,  "clicked",G_CALLBACK (radio_click_trq), &radiobutton_mode_trq);
  g_signal_connect (radiobutton_mode_imp_pos,  "clicked",G_CALLBACK (radio_click_imp_pos), &radiobutton_mode_imp_pos);
  g_signal_connect (radiobutton_mode_imp_vel,  "clicked",G_CALLBACK (radio_click_imp_vel), &radiobutton_mode_imp_vel);
  g_signal_connect (radiobutton_mode_open, "clicked",G_CALLBACK (radio_click_open), &radiobutton_mode_open);
  
  g_signal_connect (radiobutton_interaction_stiff, "clicked",G_CALLBACK (radio_click_stiff), &radiobutton_interaction_stiff);
  g_signal_connect (radiobutton_interaction_compl, "clicked",G_CALLBACK (radio_click_compl), &radiobutton_interaction_compl);

  //connection to the destroyer
  g_signal_connect (pos_winPid, "destroy",G_CALLBACK (destroy_main), &pos_winPid);
  //make it visible
  if (!GTK_WIDGET_VISIBLE (pos_winPid))
    gtk_widget_show_all (pos_winPid);
  else
    {
      gtk_widget_destroy (pos_winPid);
      pos_winPid = NULL;
    }
    
  gtk_window_set_keep_above    (GTK_WINDOW(pos_winPid),true);
  gtk_main ();

  return;
}
