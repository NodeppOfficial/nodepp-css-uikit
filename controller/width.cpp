#pragma once

namespace uk {

    express_tcp_t width() { auto app = express::http::add();

        app.ALL([=]( express_http_t cli ){ cli.send(); string_t data;

            for( auto& size: map_t<string_t,string_t>({
               { nullptr, nullptr },
               { "\\@2l", "max-width: 1600px" },
               { "\\@l" , "max-width: 1200px" },
               { "\\@m" , "max-width: 960px " },
               { "\\@s" , "max-width: 640px " },
               { "\\@portrait" , "orientation: portrait"  },
               { "\\@landscape", "orientation: landscape" },
               { "\\@mobile"   , "pointer: coarse) and (hover: none" }
               
            }).data() ){

                if( !size.first.empty() ){
                    data+=regex::format( "@media(${0}){", size.second );
                }

                for( auto x=1; x<=12; x++ ){ for( auto y=1; y<=12; y++ ){ if( x > y ){ continue; }
                    data+=( regex::format( NODEPP_STRINGIFY (
                       .uk-vw-${0}-${1}${2}    { min-width: calc( 100vw * ${0} / ${1} ); max-width: calc( 100vw * ${0} / ${1} ); }
                       .uk-width-${0}-${1}${2} { min-width: calc( ${0}00% / ${1} );      max-width: calc( ${0}00%      / ${1} ); }
                    ), x, y, size.first ));
                }}

                for( auto& item : map_t<string_t,string_t>({
                    { "none",    "0px"   },
                    { "2xsmall", "50px"  },
                    { "xsmall",  "100px" },
                    { "small",   "150px" },
                    { "medium",  "300px" },
                    { "large",   "450px" },
                    { "xlarge",  "500px" },
                    { "2xlarge", "550px" }
                }).data() ){
                    data+=( regex::format( NODEPP_STRINGIFY  (
                       .uk-width-${0}${2}{ width: calc( min( ${1}, 100vw ) ); }
                    ), item.first, item.second, size.first ));
                }

                data+=( regex::format( NODEPP_STRINGIFY (
                   .uk-width-auto${0}   { flex: auto; min-width: unset; max-width: unset; width: 100%; }
                   .uk-width-expand${0} { min-width: fit-content; }
                   .uk-width-fill${0}   { min-width: 100%; }
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
               { "\\@landscape", "orientation: landscape" },
               { "\\@mobile"   , "pointer: coarse) and (hover: none" }
            }).data() ){

                if( !size.first.empty() ){
                    data+=regex::format( "@media(${0}){", size.second );
                }

                for( auto x=1; x<=12; x++ ){ for( auto y=1; y<=12; y++ ){ if( x > y ){ continue; }
                    data+=( regex::format( NODEPP_STRINGIFY (
                       .uk-child-width-${0}-${1}${2}>:not([class*='uk-width']){ min-width: calc( ${0}00% / ${1} ); max-width: calc( ${0}00% / ${1} ); }
                    ), x, y, size.first ));
                }}

                data+=( regex::format( NODEPP_STRINGIFY (
                   .uk-child-width-auto${0}>:not([class*='uk-width'])  { flex: auto; min-width: unset; max-width: unset; width: 100%; }
                   .uk-child-width-expand${0}>:not([class*='uk-width']){ min-width: fit-content; }
                   .uk-child-width-fill${0}>:not([class*='uk-width'])  { min-width: 100%; }
                ), size.first ));

                if( !size.first.empty() ){ data+=( "}" ); }

            }

            cli.write( data );

        });

        return app;
    }

}
