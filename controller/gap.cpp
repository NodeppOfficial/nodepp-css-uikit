#pragma once

namespace uk {

    express_tcp_t gap() {
        auto app = express::http::add();

        app.ALL([=]( express_http_t cli ){ cli.send(); string_t data;

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
                    { "none",    "0px"  },
                    { "2xsmall", "5px"  },
                    { "xsmall",  "10px" },
                    { "small",   "15px" },
                    { "medium",  "25px" },
                    { "large",   "30px" },
                    { "xlarge",  "35px" },
                    { "2xlarge", "40px" }
                }).data() ){ data+=( regex::format( _STRING_(
                    .uk-child-gap-${0}${2}>:not([class*="uk-gap"]){ gap:${1}; }
                    .uk-gap-${0}${2}                              { gap:${1}; }
                ), item.first, item.second, size.first )); }

                data+=( regex::format( _STRING_(
                   .uk-child-gap${0}>:not([class*="uk-gap"]){ gap:20px; }
                   .uk-gap${0}                              { gap:20px; }
                ), size.first ));

                if( !size.first.empty() ){ data+=( "}" ); }

            }

            cli.write( data );

        });

        return app;
    }

}
