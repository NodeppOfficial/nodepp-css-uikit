#pragma once

namespace uk {

    express_tcp_t padding() {
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
                }).data() ){
                    data+=( regex::format( _STRING_ (
                       .uk-child-padding-${0}${2}>:not([class*="uk-padding"]){ padding:${1} !important; }
                       .uk-padding-${0}${2}                                  { padding:${1} !important; }
                    ), item.first, item.second, size.first ));
                }

                data+=( regex::format( _STRING_ (

                    .uk-child-padding${0}>:not([class*="uk-padding"]){ padding:20px; }
                    .uk-padding${0}                                  { padding:20px; }

                    .uk-padding-remove-bottom${0}  { padding-bottom: 0px !important; }
                    .uk-padding-remove-top${0}     { padding-top:    0px !important; }
                    .uk-padding-remove-left${0}    { padding-left:   0px !important; }
                    .uk-padding-remove-right${0}   { padding-right:  0px !important; }

                    .uk-padding-remove-horizontal${0} {
                        padding-left:  0px !important;
                        padding-right: 0px !important;
                    }

                    .uk-padding-remove-vertical${0} {
                        padding-top:    0px !important;
                        padding-bottom: 0px !important;
                    }

                    .uk-padding-remove${0} {
                        padding-left:   0px !important;
                        padding-right:  0px !important;
                        padding-top:    0px !important;
                        padding-bottom: 0px !important;
                    }

                ), size.first ));

                if( !size.first.empty() ){ data+=( "}" ); }

            }

            cli.write( data );

        });

        return app;
    }

}
