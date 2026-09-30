#pragma once

namespace uk {

    express_tcp_t border() { auto app = express::http::add();

        app.ALL([=]( express_http_t cli ){ cli.send(); queue_t<string_t> data;

            data.push( NODEPP_STRINGIFY ( .uk-border { border: solid var(--neutral) 1px; } ));

            forEach( item, ptr_t<string_t>({
                "top", "bottom", "left", "right"
            })){

                forEach( color, ptr_t<string_t>({
                    "primary", "secondary", "success",
                    "warning", "danger"   , "mute"   ,
                    "dark"   , "light"    , "none"   ,
                    "neutral"
                })){
                    data.push( regex::format( NODEPP_STRINGIFY (
                       .uk-border-${0}-${1} { border-${0}-color: var(--${1}); }
                    ), item, color ));
                }
            }

            forEach( color, ptr_t<string_t>({
                "top", "bottom", "left", "right"
            })){
                data.push( regex::format( NODEPP_STRINGIFY (
                   .uk-border-remove-${0} { border-${0}-color: var(--none); }
                ), color ));
            }

            forEach( color, ptr_t<string_t>({
                "primary", "secondary", "success",
                "warning", "danger"   , "mute"   ,
                "dark"   , "light"    , "none"   ,
                "neutral"
            })){
                data.push( regex::format( NODEPP_STRINGIFY (
                   .uk-border-${0}               { border-color: var(--${0}); }
                   .uk-border-hover-${0}:hover   { border-color: var(--${0}); }
                   .uk-border-active-${0}:active { border-color: var(--${0}); }
                ), color ));
            }

            cli.write( string::join( data, "\n" ) );

        });

        return app;
    }

}
