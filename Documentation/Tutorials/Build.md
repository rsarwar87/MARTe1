Top level git clone should be followed by

./compile <platform> <configFile> <makeMode>

Build Issues and Resolutions

Some historical notes that may be of benefit for problems in other contexts, or on new platforms.

Ubuntu 18.04 2018-06-15

Fork from github/AdamVStephen ; fix-compilation-script branch (sources on master)

11 GAMs fail to build on first attempt.

GAMs that did not compile cleanly:

DataCollectionGAM                                  
DelayGAM                                        
DigitalFilterGAM                                     
ExpEval                                              
PIDGAM                                            
PlottingGAM                                                                          
StatisticGAM                                      
StorageGAM                              
WaterTank         
WaveformGenerator2009
WebStatisticGAM          
