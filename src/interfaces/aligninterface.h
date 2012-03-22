//
// $Id$
//	
// Laidout, for laying out
// Please consult http://www.laidout.org about where to send any
// correspondence about this software.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// For more details, consult the COPYING file in the top directory.
//
// Copyright (C) 2012 by Tom Lechner
//
#ifndef INTERFACES_ALIGNINTERFACE_H
#define INTERFACES_ALIGNINTERFACE_H

#include <lax/interfaces/objectinterface.h>
#include <lax/refptrstack.h>
#include "actionarea.h"

#include "../laidout.h"


//---------------------------------- NUpInfo -----------------------------------------
enum AlignFinalLayout {
	FALIGN_None,
	FALIGN_Align,
	FALIGN_Proportional,
	FALIGN_Gap,
	FALIGN_Grid,
	FALIGN_Random,
	FALIGN_Unoverlap
};

class AlignInfo : public Laxkit::anObject, public Laxkit::RefCounted, public LaxFiles::DumpUtility
{
	//mask for what to apply from a preset:
	// snap_dir/alignment
	// layout path/type
	// single gap width
	// center
	// ui scale
  public:
	char *name;
	LaxInterfaces::SomeData *custom_icon;

	int snap_align_type;//can be FALIGN_None, FALIGN_Align, or FALIGN_Proportional
	flatvector snap_direction;
	double snapalignment;

	int final_layout_type;//FALIGN_*, none, flow+gap, random, even placement, aligned, other
	flatvector layout_direction;
	double finalalignment;//for when not flow and gap based
	double leftbound, rightbound; //line parameter for path, dist between vertices is 1

	double *gaps; //if all custom, final gap is weighted to fit in left/rightbounds?
	double defaultgap; //apply initially, but user can adjust per gap after
	int gaptype; //whether custom for whole list (weighted or absolute), or single value gap, or function gap

	int flags;//align matrix, or shift only
	flatvector center;
	double uiscale; //width of main alignment bar
	LaxInterfaces::PathsData *line; //custom alignment path

	AlignInfo();
	virtual ~AlignInfo();

	virtual void dump_out(FILE*, int, int, Laxkit::anObject*);
	virtual void dump_in_atts(LaxFiles::Attribute*, int, Laxkit::anObject*);
};


//------------------------------------- AlignInterface --------------------------------------

class AlignInterface : public LaxInterfaces::ObjectInterface
{
  protected:
	Laxkit::ButtonDownInfo buttondown;

	AlignInfo *aligninfo;
	Laxkit::NumStack<flatpoint> controls;
	Laxkit::NumStack<double> controlamount;

	Laxkit::RefPtrStack<LaxInterfaces::SomeData> original_transforms;

	int showdecs;
	int firsttime;
	int active; //whether to continuously apply changes

	unsigned int controlcolor;

	virtual int scan(int x,int y);
	virtual int onPath(int x,int y);
	//virtual void createControls();
	//virtual void remapControls();
  public:
	int snapto_lrc_amount;

	AlignInterface(int nid=0,Laxkit::Displayer *ndp=NULL,Document *ndoc=NULL);
	AlignInterface(anInterface *nowner=NULL,int nid=0,Laxkit::Displayer *ndp=NULL);
	virtual ~AlignInterface();
	virtual anInterface *duplicate(anInterface *dup=NULL);

	virtual const char *IconId() { return "Align"; }
	virtual const char *Name();
	virtual const char *whattype() { return "AlignInterface"; }
	virtual const char *whatdatatype() { return NULL; }
	virtual int draws(const char *atype);

	virtual int InterfaceOn();
	virtual int InterfaceOff(); 
	virtual void Clear(LaxInterfaces::SomeData *d);
	virtual Laxkit::MenuInfo *ContextMenu(int x,int y,int deviceid);
	virtual int Event(const Laxkit::EventData *e,const char *mes);

	
	 // return 0 if interface absorbs event, MouseMove never absorbs: must return 1;
	virtual int LBDown(int x,int y,unsigned int state,int count,const Laxkit::LaxMouse *d);
	virtual int LBUp(int x,int y,unsigned int state,const Laxkit::LaxMouse *d);
	virtual int WheelUp(int x,int y,unsigned int state,int count,const Laxkit::LaxMouse *d);
	virtual int WheelDown(int x,int y,unsigned int state,int count,const Laxkit::LaxMouse *d);
	virtual int MouseMove(int x,int y,unsigned int state,const Laxkit::LaxMouse *mouse);
	virtual int CharInput(unsigned int ch, const char *buffer,int len,unsigned int state,const Laxkit::LaxKeyboard *d);
	virtual int KeyUp(unsigned int ch,unsigned int state,const Laxkit::LaxKeyboard *d);
	virtual int Refresh();
	virtual void DrawAlignBox(flatpoint dir, double amount, int with_arrows, int with_rotation_handles);
	
	virtual int UseThis(Laxkit::anObject *ndata,unsigned int mask=0); 
	virtual int FreeSelection();
	virtual int AddToSelection(Laxkit::PtrStack<LaxInterfaces::ObjectContext> &objs);
	//virtual int AddToSelection(Laxkit::PtrStack<ObjectContext> &objs);

	virtual int ApplyAlignment(int updateorig);
	virtual int ResetAlignment();
	virtual int PointToLine(flatpoint p, flatpoint &ip, int isfinal);
	virtual int PointToPath(flatpoint p, flatpoint &ip);
};



#endif

