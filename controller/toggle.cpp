#pragma once

namespace uk {

    express_tcp_t toggle() {
        auto app = express::http::add();

        app.ALL([=]( express_http_t cli ){ cli.send(); string_t data;

            data+=( _STRING_( [toggle=""]:not(input):has(input[toggle]:checked) { display: none !important; } ));
            data+=( _STRING_( [toggle-hover=""]:not(:hover) [toggle]{ display: none !important; } ));

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

                for( auto x=0; x<=12; x++ ){
                    data+=( regex::format( _STRING_(
                       body:has(input[class="uk-toggle-${0}${1}"]:checked)       [toggle="${0}"] { display: none !important; }
                       body:has(input[class="uk-toggle-${0}${1}"]:not(:checked)) [toggle="!${0}"]{ display: none !important; }
                    ), x, size.first ));
                }

                if( !size.first.empty() ){ data+=( "}" ); }

            }

            cli.write( data );

        });

        return app;
    }

}
