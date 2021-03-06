#include "../include/View.h"
#include "../external/plustache/include/template.hpp"
#include "../external/plustache/include/context.hpp"


using namespace CouchFine;


View View::valueOf(
    const std::string& folder,
    const std::map< std::string, std::string >&  context
) {
    namespace fs = boost::filesystem;

    assert( fs::exists( folder ) && "Folder is not exists." );
    assert( fs::is_directory( folder ) && "Path is not directory." );

    // �������� �������������
    const std::string name = fs::basename( folder );

    const std::string f = folder
      + ( (folder[ folder.length() - 1 ] == '/') ? "" : "/" );

    const std::string map = f + "map.js";
    assert( fs::exists( map ) && "File 'map.js' is not exists." );
    std::ifstream fMap( f );
    std::string sMap = std::string(
        std::istreambuf_iterator< char >( fMap ),
        std::istreambuf_iterator< char >()
    );

    // reduce.js - �� ������������ ����
    const std::string reduce = f + "reduce.js";
    std::string sReduce = "";
    if ( fs::exists( reduce ) ) {
        std::ifstream fReduce( f );
        sReduce = std::string(
            std::istreambuf_iterator< char >( fReduce ),
            std::istreambuf_iterator< char >()
        );
    }

    // ����� ��������� �������� ���������
    if ( !context.empty() ) {
        template_t t;
        sMap = t.render( sMap, context );
        sReduce = t.render( sReduce, context );
    }

    return View( name, sMap, sReduce );
}
