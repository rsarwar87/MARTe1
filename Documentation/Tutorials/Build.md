Top level git clone should be followed by

./compile <platform> <configFile> <makeMode>

Build Issues and Resolutions

Some historical notes that may be of benefit for problems in other contexts, or on new platforms.

Ubuntu 18.04 2018-06-15

Fork from github/AdamVStephen ; fix-compilation-script branch (sources on master)

11 GAMs fail to build on first attempt.

GAMs that did not compile cleanly:

1. DataCollectionGAM                                  
1.1 Repeat manual build in local directory succeeeds
1. DelayGAM                                        
1.1 Repeat manual build in local directory succeeeds
1. DigitalFilterGAM                                     
1.1 Erroneous error : library already built.
1. ExpEval                                              
1.1 Erroneous error : library already built.
1. PIDGAM                                            
1.1 Repeat manual build in local directory succeeeds
1. PlottingGAM                                                                          
1.1 Erroneous error : library already built.
1. StatisticGAM                                      
1.1 Erroneous error : library already built.
1. StorageGAM                              
1.1 Erroneous error : library already built.
1.1 WaterTank         
1.1 Erroneous error : library already built.
1. WaveformGenerator2009
1.1 No linux/ directory because depends target fails due to dependency on non-existence ExpressionEvaluator2009 in WaveformEquationSolver
1.2 Makefile.inc has commented out WaveformEquationSolver module but the depends rules still find matching on pattern.
1.3 Solution : rename the code to be suffixed .disabled
1.4 Solution : make the top level depends rules work to create the linux/ subdirectory first (ewhittaker fork)
1. WebStatisticGAM          
1.1 Erroneous error : library already built.

Now investigate the common errors.

(a) Erroneous report that first build had some errors relating to e.g. DigitalFilterGam.  Firstly ensure this is correct, so run a clean compile from the top level.
- Ref https://stackoverflow.com/questions/24771737/include-generated-makefile-without-warning-message
- Ref http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
