
string    ifs_file_name = ""; 
ifstream  ifs;                       

ifs.open ( ifs_file_name.c_str() ); 
if ( !ifs ) 
{
	cerr << "\nERROR : failed to open input  file " << ifs_file_name << endl;
	exit (-1);
}
{-continue_here-}
ifs.close ();                     


string    ofs_file_name = "";
ofstream  ofs;                      

ofs.open ( ofs_file_name.c_str() );
if ( !ofs ) 
{
	cerr << "\nERROR : failed to open output file " << ofs_file_name << endl;
	exit (-1);
}
{-continue_here-}
ofs.close ();            
