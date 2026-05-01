#pragma once

namespace uk {

    express_tcp_t visibility() {
        auto app = express::http::add();

        app.ALL([=]( express_http_t cli ){ cli.send(); string_t data;

            for( auto& size: map_t<string_t,string_t>({
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

                data+=( regex::format( _STRING_(
                   .uk-visible${0} { display: none !important; }
                ), size.first ));

                if( !size.first.empty() ){ data+=( "}" ); }

            }

            for( auto& size: map_t<string_t,string_t>({
               { nullptr, nullptr },
               { "\\@2l", "max-width: 1600px" },
               { "\\@l" , "max-width: 1200px" },
               { "\\@m" , "max-width: 960px " },
               { "\\@s" , "max-width: 640px " },
               { "\\@portrait" , "orientation: portrait"  },
               { "\\@landscape", "orientation: landscape" }
            }).data() ){

                if( !size.first.empty() ){
                    data+=regex::format( "@media(${0}){", size.second );
                }

                data+=( regex::format( _STRING_(
                   .uk-hidden${0} { display: none !important; }
                ), size.first ));

                if( !size.first.empty() ){ data+=( "}" ); }

            }

            cli.write( data );

        });

        return app;
    }

}
