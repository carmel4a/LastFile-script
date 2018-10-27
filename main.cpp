#include <iostream>
#include <filesystem>
#include <string>
#include <regex>
#include <vector>

constexpr char regex_to_find_files[] = ".";

void print_help();

int main( int args_number, char** args )
{
	if( args_number <= 1
	 || std::string( args[1] ) == "-h"
	 || std::string( args[1] ) == "--help")
	{
		print_help();
		return 1;
	}
	std::filesystem::path path { std::filesystem::u8path( args[1] ) };
	std::filesystem::current_path( path );
	
	std::filesystem::directory_entry cur_dir;
	cur_dir.assign( path );
	
	std::vector< std::filesystem::path > files_found;

	std::regex files_regex { (args_number == 3)
			? args[2]
			: regex_to_find_files };
	
	for( auto& x : std::filesystem::directory_iterator( cur_dir ) )
		if( ( x.is_regular_file() || x.is_symlink() )
		 && std::regex_search( (std::string) x.path(), files_regex ) )
			files_found.push_back( std::filesystem::absolute( x ) );
			
	if( files_found.empty() )
	{
		std::cout << "No file matching to regex was found.";
		return 0;
	}
	auto last_file = files_found.begin();
	for( auto x = files_found.begin(); x != files_found.end(); ++x )	
		if( std::filesystem::directory_entry( *x         ).last_write_time()
		  > std::filesystem::directory_entry( *last_file ).last_write_time() )
			last_file = x;
	if( files_found.size() == 1 ) return 0;
	files_found.erase( last_file );
  begin:
	for( auto x = files_found.begin(); x != files_found.end(); ++x )
	{
		std::filesystem::remove( *x );
		files_found.erase(x);
		goto begin;
	}
	return 0;
}

void print_help()
{
	std::cout
			<< "Usage:"                            << std::endl
			<< "$ newest_file path_to_dic [regex]" << std::endl;
}
