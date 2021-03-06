#include <queue>

cmsListDir( const TObjString * firstdirname, const TDirectory * firstDir )
 {
  TObjArray * dirs = new TObjArray ;
  dirs->AddLast(new TPair(firstdirname,firstDir)) ;
  TList * keys ;
  TKey * key ;
  TH1 * histo ;
  TIter nextDir(dirs) ;
  TPair * pair ;
  const TObjString * dirname ;
  const TDirectory * dir ;
  while (pair = (TPair *)nextDir())
   {
    dirname = (TObjString *)pair->Key() ;
    dir = (TDirectory *)pair->Value() ;
    keys = dir->GetListOfKeys() ;
    TIter nextKey(keys) ;
    while (key = (TKey *)nextKey())
     {
      obj = key->ReadObj() ;
      if (obj->IsA()->InheritsFrom("TDirectory"))
       {
        dirs->AddLast(new TPair(new TObjString(dirname->String()+"/"+obj->GetName()),obj)) ;
       }
      else if (obj->IsA()->InheritsFrom("TH1"))
       {
        histo = (TH1 *)obj ;
        std::cout
          <<"Histo "<<dirname->String()<<"/"<<histo->GetName()
          <<" has "<<histo->GetEffectiveEntries()<<" entries"
          <<" of mean value "<<histo->GetMean()
          <<std::endl ;
       }
      else
       { std::cout<<"What is "<<obj->GetName()<<" ?"<<std::endl ; }
     }
   }
 }

cmsListHistos()
 {
  TString input_file_name = gSystem->Getenv("TEST_INPUT_FILE") ;
  TString internal_path("DQMData/Run 1/EgammaV/Run summary") ;

  input_file = TFile::Open(input_file_name) ;
  if (input_file!=0)
   {
    std::cout<<"open "<<input_file_name<<std::endl ;
    if (input_file->cd(internal_path)!=kTRUE)
     {
      std::cerr<<"Failed move to: "<<internal_path<<std::endl ;
      cmsListDir("",gDirectory) ;
     }
    else
     {
      std::cout<<"cd "<<internal_path<<std::endl ;
      cmsListDir(new TObjString(internal_path),gDirectory) ;
     }
   }
  else
   {
    std::cerr<<"Failed to open: "<<input_file_name<<std::endl ;
    return ;
   }
  input_file->Close() ;
 }
