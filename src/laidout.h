#ifndef LAIDOUT_H
#define LAIDOUT_H

#include <lax/anxapp.h>

#include "disposition.h"
#include "papersizes.h"
#include "document.h"
#include "newdoc.h"
#include "interfaces.h"

const char *LaidoutVersion();

class LaidoutApp : public Laxkit::anXApp
{
 public:
//	ControlPanel *maincontrolpanel;
	Project *project;
	Document *curdoc;
	
//	Laxkit::PtrStack<Style> stylestack:
//	Laxkit::PtrStack<FontThing> fontstack;
//	Laxkit::PtrStack<Project> projectstack;
//	ScreenStyle *screen;
	Laxkit::PtrStack<Laxkit::anInterface> interfacepool;
	Laxkit::PtrStack<Disposition> dispositionpool;
	Laxkit::PtrStack<PaperType> papersizes;
	LaidoutApp();
	virtual ~LaidoutApp();
	virtual int init(int argc,char **argv);
	virtual void setupdefaultcolors();
	void parseargs(int argc,char **argv);

	Document *LoadDocument(const char *filename);
	int NewDocument(DocumentStyle *docinfo, const char *filename);
	int NewDocument(const char *spec);

	void notifyDocTreeChanged(Laxkit::anXWindow *callfrom=NULL);
};

// if included in laidout.cc, then don't include "extern" when defining *laidout
#ifndef LAIDOUT_CC
extern
#endif
LaidoutApp *laidout;


#endif

