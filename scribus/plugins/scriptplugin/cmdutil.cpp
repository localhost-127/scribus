#include "cmdutil.h"

ScribusApp* Carrier;
ScribusDoc* doc;

double PointToValue(double Val)
{
	double ret = 0.0;
	switch (Carrier->doc->Einheit)
	{
	case 0:
		ret = Val;
		break;
	case 1:
		ret = Val * 0.3527777;
		break;
	case 2:
		ret = Val * (1.0 / 72.0);
		break;
	case 3:
		ret = Val * (1.0 / 12.0);
		break;
	}
	return ret;
}

double ValToPts(double Val, int ein)
{
	double ret = 0.0;
	switch (ein)
	{
	case 0:
		ret = Val;
		break;
	case 1:
		ret = Val / 0.3527777;
		break;
	case 2:
		ret = Val / (1.0 / 72.0);
		break;
	case 3:
		ret = Val / (1.0 / 12.0);
		break;
	}
	return ret;
}

double ValueToPoint(double Val)
{
	return ValToPts(Val, Carrier->doc->Einheit);
}

int GetItem(QString Name)
{
	if (Name != "")
	{
		for (uint a = 0; a < Carrier->doc->Items.count(); a++)
		{
			if (Carrier->doc->Items.at(a)->AnName == Name)
				return static_cast<int>(a);
		}
	}
	else
	{
		if (Carrier->view->SelItem.count() != 0)
			return Carrier->view->SelItem.at(0)->ItemNr;
	}
	return -1;
}

void ReplaceColor(QString col, QString rep)
{
	QColor tmpc;
	for (uint c = 0; c < Carrier->doc->Items.count(); c++)
	{
		PageItem *ite = Carrier->doc->Items.at(c);
		if (ite->PType == 4)
		{
			for (uint d = 0; d < ite->Ptext.count(); d++)
			{
				if (col == ite->Ptext.at(d)->ccolor)
					ite->Ptext.at(d)->ccolor = rep;
				if (col == ite->Ptext.at(d)->cstroke)
					ite->Ptext.at(d)->cstroke = rep;
			}
		}
		if (col == ite->Pcolor)
			ite->Pcolor = rep;
		if (col == ite->Pcolor2)
			ite->Pcolor2 = rep;
		QPtrVector<VColorStop> cstops = ite->fill_gradient.colorStops();
		for (uint cst = 0; cst < ite->fill_gradient.Stops(); ++cst)
		{
			if (col == cstops.at(cst)->name)
			{
				ite->SetFarbe(&tmpc, rep, cstops.at(cst)->shade);
				cstops.at(cst)->color = tmpc;
				cstops.at(cst)->name = rep;
			}
		}
	}
	for (uint c = 0; c < Carrier->doc->MasterItems.count(); c++)
	{
		PageItem *ite = Carrier->doc->MasterItems.at(c);
		if (ite->PType == 4)
		{
			for (uint d = 0; d < ite->Ptext.count(); d++)
			{
				if (col == ite->Ptext.at(d)->ccolor)
					ite->Ptext.at(d)->ccolor = rep;
				if (col == ite->Ptext.at(d)->cstroke)
					ite->Ptext.at(d)->cstroke = rep;
			}
		}
		if (col == ite->Pcolor)
			ite->Pcolor = rep;
		if (col == ite->Pcolor2)
			ite->Pcolor2 = rep;
		QPtrVector<VColorStop> cstops = ite->fill_gradient.colorStops();
		for (uint cst = 0; cst < ite->fill_gradient.Stops(); ++cst)
		{
			if (col == cstops.at(cst)->name)
			{
				ite->SetFarbe(&tmpc, rep, cstops.at(cst)->shade);
				cstops.at(cst)->color = tmpc;
				cstops.at(cst)->name = rep;
			}
		}
	}
}

/* 04/07/10 returns selection if is not name specified  pv  */
PageItem* GetUniqueItem(QString name)
{
	if (name.length()==0)
		if (Carrier->view->SelItem.count() != 0)
			return Carrier->view->SelItem.at(0);
	if (name.length()==0) // in the case of no selection and ""
		return NULL;
	for (uint j = 0; j<Carrier->doc->Items.count(); j++)
	{
		if (name==Carrier->doc->Items.at(j)->AnName)
			return Carrier->doc->Items.at(j);
	} // for items
	return NULL;
}
