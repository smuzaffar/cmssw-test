// -*- C++ -*-
//
// Package:    MultiplicityInvestigator
// Class:      MultiplicityInvestigator
//
/**\class MultiplicityInvestigator MultiplicityInvestigator.cc myTKAnalyses/DigiInvestigator/src/MultiplicityInvestigator.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andrea Venturi
//         Created:  Mon Oct 27 17:37:53 CET 2008
// $Id: MultiplicityInvestigator.cc,v 1.5 2012/02/15 11:13:25 venturia Exp $
//
//


// system include files
#include <memory>

// user include files

#include <vector>
#include <map>
#include <limits>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DPGAnalysis/SiStripTools/interface/DigiInvestigatorHistogramMaker.h"
#include "DPGAnalysis/SiStripTools/interface/DigiVertexCorrHistogramMaker.h"
#include "DPGAnalysis/SiStripTools/interface/DigiLumiCorrHistogramMaker.h"
#include "DPGAnalysis/SiStripTools/interface/DigiPileupCorrHistogramMaker.h"

//
// class decleration
//

class MultiplicityInvestigator : public edm::EDAnalyzer {
   public:
      explicit MultiplicityInvestigator(const edm::ParameterSet&);
      ~MultiplicityInvestigator();


private:
  virtual void beginJob() override ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void beginRun(const edm::Run&, const edm::EventSetup&) override;
  virtual void endJob() override ;

      // ----------member data ---------------------------

  const bool m_wantInvestHist;
  const bool m_wantVtxCorrHist;
  const bool m_wantLumiCorrHist;
  const bool m_wantPileupCorrHist;
  DigiInvestigatorHistogramMaker m_digiinvesthmevent;
  DigiVertexCorrHistogramMaker m_digivtxcorrhmevent;
  DigiLumiCorrHistogramMaker m_digilumicorrhmevent;
  DigiPileupCorrHistogramMaker m_digipileupcorrhmevent;

  edm::EDGetTokenT<std::map<unsigned int, int> > m_multiplicityMapToken;
  edm::EDGetTokenT<reco::VertexCollection> m_vertexCollectionToken;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MultiplicityInvestigator::MultiplicityInvestigator(const edm::ParameterSet& iConfig):
  //  m_digiinvesthmevent(iConfig.getParameter<edm::ParameterSet>("digiInvestConfig"), consumesCollector()),
  m_wantInvestHist(iConfig.getParameter<bool>("wantInvestHist")),
  m_wantVtxCorrHist(iConfig.getParameter<bool>("wantVtxCorrHist")),
  m_wantLumiCorrHist(iConfig.getParameter<bool>("wantLumiCorrHist")),
  m_wantPileupCorrHist(iConfig.getParameter<bool>("wantPileupCorrHist")),
  m_digiinvesthmevent(iConfig, consumesCollector()),
  m_digivtxcorrhmevent(iConfig.getParameter<edm::ParameterSet>("digiVtxCorrConfig")),
  m_digilumicorrhmevent(iConfig.getParameter<edm::ParameterSet>("digiLumiCorrConfig"), consumesCollector()),
  m_digipileupcorrhmevent(iConfig.getParameter<edm::ParameterSet>("digiPileupCorrConfig"), consumesCollector()),
  m_multiplicityMapToken(consumes<std::map<unsigned int, int> >(iConfig.getParameter<edm::InputTag>("multiplicityMap"))),
  m_vertexCollectionToken(mayConsume<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertexCollection")))
{
   //now do what ever initialization is needed


  if(m_wantInvestHist)  m_digiinvesthmevent.book("EventProcs");
  if(m_wantVtxCorrHist) m_digivtxcorrhmevent.book("VtxCorr", consumesCollector());
  if(m_wantLumiCorrHist) m_digilumicorrhmevent.book("LumiCorr", consumesCollector());
  if(m_wantPileupCorrHist) m_digipileupcorrhmevent.book("PileupCorr");

}


MultiplicityInvestigator::~MultiplicityInvestigator()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
MultiplicityInvestigator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  Handle<std::map<unsigned int, int> > mults;
  iEvent.getByToken(m_multiplicityMapToken,mults);

  if(m_wantInvestHist) m_digiinvesthmevent.fill(iEvent.orbitNumber(),*mults);

  if(m_wantVtxCorrHist) {
    Handle<reco::VertexCollection> vertices;
    iEvent.getByToken(m_vertexCollectionToken,vertices);

    m_digivtxcorrhmevent.fill(iEvent,vertices->size(),*mults);
  }

  if(m_wantLumiCorrHist) m_digilumicorrhmevent.fill(iEvent,*mults);
  if(m_wantPileupCorrHist) m_digipileupcorrhmevent.fill(iEvent,*mults);

}


// ------------ method called once each job just before starting event loop  ------------
void
MultiplicityInvestigator::beginJob()
{

}

void
MultiplicityInvestigator::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup) {

  m_digiinvesthmevent.beginRun(iRun.run());
  m_digivtxcorrhmevent.beginRun(iRun);
  m_digilumicorrhmevent.beginRun(iRun);

}
// ------------ method called once each job just after ending the event loop  ------------
void
MultiplicityInvestigator::endJob() {
}
//define this as a plug-in
DEFINE_FWK_MODULE(MultiplicityInvestigator);
