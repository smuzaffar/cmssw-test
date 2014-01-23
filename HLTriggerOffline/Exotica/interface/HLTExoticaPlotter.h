#ifndef HLTriggerOffline_Exotica_HLTExoticaPlotter_H
#define HLTriggerOffline_Exotica_HLTExoticaPlotter_H

/** \class HLTExoticaPlotter
 *  Generate histograms for trigger efficiencies Exotica related
 *  Documentation available on the CMS TWiki:
 *  https://twiki.cern.ch/twiki/bin/view/CMS/ExoticaWGHLTValidate
 *
 *  \author  J. Duarte Campderros (based and adapted on J. Klukas,
 *           M. Vander Donckt and J. Alcaraz code from the 
 *           HLTriggerOffline/Muon package)
 *  \author  J. Klukas, M. Vander Donckt, J. Alcaraz
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/HLTReco/interface/TriggerEventWithRefs.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidateFwd.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include "HLTriggerOffline/Exotica/src/MatchStruct.cc"

#include <vector>
#include <cstring>
#include <map>
#include <set>

const unsigned int kNull = (unsigned int) -1;

class EVTColContainer;

class HLTExoticaPlotter 
{
       	public:
	      	HLTExoticaPlotter(const edm::ParameterSet & pset, const std::string & hltPath,
				//const std::string & lastFilter,
				const std::vector<unsigned int> & objectsType,
			       	DQMStore * dbe);
		~HLTExoticaPlotter();
	      	void beginJob();
	      	void beginRun(const edm::Run &, const edm::EventSetup &);
		void analyze(const bool & isPassTrigger,const std::string & source,
				const std::vector<MatchStruct> & matches);
		
		inline const std::string gethltpath() const { return _hltPath; }
		
       	private:
	      	void bookHist(const std::string & source, const std::string & objType, const std::string & variable);
	      	void fillHist(const bool & passTrigger, const std::string & source, 
				const std::string & objType, const std::string & var, 
				const float & value);
		
	      	std::string _hltPath;
		//std::string _lastFilter;
		std::string _hltProcessName;

		std::set<unsigned int> _objectsType;
		// Number of objects (elec,muons, ...) needed in the hlt path
		unsigned int _nObjects; 
		
	      	std::vector<double> _parametersEta;
	      	std::vector<double> _parametersPhi;
	      	std::vector<double> _parametersTurnOn;
		
	      	DQMStore* _dbe;
	      	std::map<std::string, MonitorElement *> _elements;		
};
#endif
