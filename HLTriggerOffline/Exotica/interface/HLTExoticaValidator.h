#ifndef HLTriggerOffline_Exotica_HLTExoticaValidator_H
#define HLTriggerOffline_Exotica_HLTExoticaValidator_H

/** \class HLTExoticaValidator
 *  Generate histograms for trigger efficiencies Exotica related
 *  Documentation available on the CMS TWiki:
 *  https://twiki.cern.ch/twiki/bin/view/CMS/ExoticaWGHLTValidate
 *
 *  \author  Thiago R. Fernandez Perez Tomei 
 *           Based and adapted from:
 *           Duarte Campderros code from HLTriggerOffline/Higgs and 
 *           J. Klukas, M. Vander Donckt and J. Alcaraz code 
 *           from the HLTriggerOffline/Muon package.
 */

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DQMServices/Core/interface/DQMStore.h"

#include "HLTriggerOffline/Exotica/interface/HLTExoticaSubAnalysis.h"

#include <vector>
#include <cstring>


class EVTColContainer;

//! The HLTExoticaValidator module is the main module of the
//! package. More discussion to come.
class HLTExoticaValidator : public edm::EDAnalyzer 
{
	public:
		//! Constructor
	      	HLTExoticaValidator(const edm::ParameterSet &);
	      	~HLTExoticaValidator();

	private:
		// concrete analyzer methods
	      	virtual void beginJob();
	      	virtual void beginRun(const edm::Run &iRun, const edm::EventSetup & iSetup);
	      	virtual void analyze(const edm::Event & iEvent, const edm::EventSetup & iSetup);
		virtual void endRun(const edm::Run & iRun, const edm::EventSetup & iSetup);
		virtual void endJob();

		//! Input from configuration file
		edm::ParameterSet _pset;
		//! the names of the subanalyses
		std::vector<std::string> _analysisnames;
		
		//! The instances of the class which do the real work
		std::vector<HLTExoticaSubAnalysis> _analyzers;
				
		//! The container with all the collections needed
		EVTColContainer * _collections;
		
		// Access to the DQM
		DQMStore * _dbe;      	
};

#endif
