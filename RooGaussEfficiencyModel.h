/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id$
 * Authors:                                                                  *
 *   GR, Gerhard Raven, VU&Nikhef Amsterdam
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_CS_GAUSS_MODEL
#define ROO_CS_GAUSS_MODEL

#include <complex>
#include "RooResolutionModel.h"
#include "RooRealProxy.h"

#include "RooAbsEffResModel.h"

class RooAbsReal;
class RooRealVar;
class RooAbsGaussModelEfficiency;

class RooGaussEfficiencyModel : public RooResolutionModel, public RooAbsEffResModel {
public:

  // Constructors, assignment etc
  inline RooGaussEfficiencyModel() : _flatSFInt(kFALSE)  { }
  RooGaussEfficiencyModel(const char *name, const char *title,
            RooRealVar& x, RooAbsGaussModelEfficiency& spline,
            RooAbsReal& mean,   RooAbsReal& sigma );
  RooGaussEfficiencyModel(const char *name, const char *title,
            RooRealVar& x, RooAbsGaussModelEfficiency& spline,
            RooAbsReal& mean,   RooAbsReal& sigma,
            RooAbsReal& meanSF, RooAbsReal& sigmaSF) ;
  RooGaussEfficiencyModel(const RooGaussEfficiencyModel& other, const char* name=0);
  virtual ~RooGaussEfficiencyModel();

  TObject* clone(const char* newname) const override { return new RooGaussEfficiencyModel(*this,newname) ; }

  Int_t basisCode(const char* name) const override;
  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const override;
  Double_t analyticalIntegral(Int_t code, const char* rangeName) const override;

  // TODO: move this one to the mixin-interface
  RooAbsGenContext* modelGenContext(const RooAbsAnaConvPdf& convPdf, const RooArgSet &vars,
                                     const RooDataSet *prototype=0, const RooArgSet* auxProto=0,
                                     Bool_t verbose= kFALSE) const override;
  Bool_t isDirectGenSafe(const RooAbsArg& arg) const override;
  Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK) const override;
  void generateEvent(Int_t code) override;

  void advertiseFlatScaleFactorIntegral(Bool_t flag) { _flatSFInt = flag ; }

  const RooAbsReal* efficiency() const override;
  RooArgSet* observables() const override;

private:

  Double_t evaluate() const override;

  std::complex<double> evalInt(Double_t xmin, Double_t xmax,
                               Double_t scale, Double_t offset,
                               const std::complex<double>& z) const;
  Bool_t _flatSFInt ;

  RooRealProxy eff ;
  RooRealProxy mean ;
  RooRealProxy sigma ;
  RooRealProxy msf ;
  RooRealProxy ssf ;

  ClassDefOverride(RooGaussEfficiencyModel,1)
};

#endif
