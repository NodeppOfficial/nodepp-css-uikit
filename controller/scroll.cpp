#pragma once

namespace uk { express_tcp_t scroll() { auto app = express::http::add();

    app.ALL([=]( express_http_t cli ){ cli.send(); queue_t<string_t> data;

        data.push( NODEPP_STRINGIFY (

            *:not([class*='uk-scroll']) { scrollbar-width: none; }
            *:not([class*='uk-scroll'])::-webkit-scrollbar {
                background: transparent;
                width: 0; height: 0;
            }

        ));

        for( auto& size: map_t<string_t,string_t>({
           { nullptr, nullptr },
           { "\\@portrait" , "orientation: portrait"  },
           { "\\@landscape", "orientation: landscape" },
           { "\\@mobile"   , "pointer: coarse) and (hover: none" },
           { "\\@desktop"  , "pointer: fine  ) and (hover: none" },
           { "\\@console"  , "pointer: none  ) and (hover: none" }
        }).data() ){

            if( !size.first.empty() ){
                data.push( regex::format( "@media(${0}){", size.second ) );
            }

            data.push( regex::format( NODEPP_STRINGIFY (

                .uk-scroll-hidden${0} { scrollbar-width: none; }
                .uk-scroll-hidden${0} ::-webkit-scrollbar {
                    background: transparent;
                    height: 0 ; width: 0; 
                }

                .uk-scroll-x${0} {
                    scrollbar-height: 0.3em;
                    scrollbar-width:  0.0em;
                }

                .uk-scroll-y${0} {
                    scrollbar-height: 0.0em;
                    scrollbar-width:  0.3em;
                }

                .uk-scroll${0} {
                    scrollbar-height: 0.3em;
                    scrollbar-width:  0.3em;
                }

                .uk-scroll-x${0}::-webkit-scrollbar { height: 0.3em; width: 0.0em; }
                .uk-scroll-y${0}::-webkit-scrollbar { height: 0.0em; width: 0.3em; }
                .uk-scroll${0}::-webkit-scrollbar   { height: 0.3em; width: 0.3em; }

            ), size.first ));

            for( auto& color : array_t<string_t>({
                "primary", "secondary", "success",
                "warning", "danger"   , "mute"   ,
                "light"  , "dark"     , "neutral"
            })){ 
                
                data.push( regex::format( NODEPP_STRINGIFY (

                    .uk-scroll-${0}${1}::-webkit-scrollbar-thumb {
                        background-color: var(--${0});
                    }

                    .uk-scroll-${0}${1} {
                        scrollbar-color: var(--${0}) transparent;
                    }

                ), color, size.first )); 
        
            }

            if( !size.first.empty() ){ data.push( "}" ); }
        
        } cli.write( string::join( data, "\n" ) );

    }); return app;

}}
