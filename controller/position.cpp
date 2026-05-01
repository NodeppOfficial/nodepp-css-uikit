#pragma once

namespace uk {

    express_tcp_t position() {
        auto app = express::http::add();

        app.ALL([=]( express_http_t cli ){ cli.send(); string_t data;

            data+=( _STRING_( [class*=uk-position]{ position: absolute; }));

            for( auto& size: map_t<string_t,string_t>({
               { nullptr, nullptr },
               { "\\@2l", "min-width: 1600px" },
               { "\\@l" , "min-width: 1200px" },
               { "\\@m" , "min-width: 960px " },
               { "\\@s" , "min-width: 640px " },
               { "\\@portrait" , "orientation: portrait"  },
               { "\\@landscape", "orientation: landscape" }
            }).data() ){

                if( !size.first.empty() ){
                    data+=regex::format( "@media(${0}){", size.second );
                }

                for( auto& item : map_t<string_t,string_t>({
                    { "center"      ,"top:   50%; left: 50%;" },
                    { "bottom"      ,"bottom: 0%; left: 50%"  },
                    { "bottom-left" ,"bottom: 0%; left:  0%;" },
                    { "bottom-right","bottom: 0%; right: 0%;" },
                    { "top"         ,"top:    0%; left: 50%;" },
                    { "top-left"    ,"top:    0%; left:  0%;" },
                    { "top-right"   ,"top:    0%; right: 0%;" },
                    { "left"        ,"top:   50%; left:  0%;" },
                    { "right"       ,"top:   50%; right: 0%;" },
                    { "fixed"       ,"position: fixed    !important;"            },
                    { "relative"    ,"position: relative !important;"            },
                    { "absolute"    ,"position: absolute !important;"            },
                    { "sticky"      ,"position: sticky   !important; top: 20px;" }
                }).data() ){
                    data+=( regex::format( _STRING_(
                       .uk-position-${0}${2} { ${1} }
                    ), item.first, item.second, size.first ));
                }

                if( !size.first.empty() ){ data+=( "}" ); }

            }

            cli.write( data );

        });

        return app;
    }

}
