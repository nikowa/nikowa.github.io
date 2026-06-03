#include "generator/generator.h"

extern Generator* generator;

const String COLOR_FOREGROUND_STRING = COMPTIME_STRING("#2b2b2b");
const String COLOR_BACKGROUND_STRING = COMPTIME_STRING("#F7F5F2");
const String STROKE = COMPTIME_STRING("1px solid #2b2b2b");
const String SHADOW = COMPTIME_STRING("5px 5px #d6d5eb");

#define GRID_CONTAINER() pgprint_div_element_block((Global_Attributes){ .class = STRING("grid-container") })
#define CAPTION(x) pgprint_div_element_block((Global_Attributes){ .class = STRING("caption") }) {\
	pgprint_string(STRING(x)); }
#define GRID_ITEM(caption, link, thumbnail) pgprint_div_element_block((Global_Attributes){ .class = STRING("grid-item") }) {\
	pgprint_a_element_block(STRING(link), DEFAULT_GLOBAL_ATTRIBUTES) {\
		pgprint_img_element(STRING(thumbnail));\
		CAPTION(caption); } }

void pgprint_head() {
	pgprint_head_element_block(DEFAULT_GLOBAL_ATTRIBUTES) {
		pgprint_meta_charset_element();
		pgprint_title_element(STRING("Nikola Stefanov"), DEFAULT_GLOBAL_ATTRIBUTES);
		pgprint_script_element(STRING("script.js"), false);
		pgprint_link_stylesheet_element(STRING("/style.css")); } }

void pgprint_header(String title) {
	// pgprint_div_element_block((Global_Attributes){ .class = STRING("overlay") });
	pgprint_header_element_block((Global_Attributes){ .class = STRING("my-header") }) {
		pgprint_h1_element(title, DEFAULT_GLOBAL_ATTRIBUTES);
		pgprint_ul_element_block(DEFAULT_GLOBAL_ATTRIBUTES) {
			pgprint_li_element_block(DEFAULT_GLOBAL_ATTRIBUTES) {
				pgprint_a_element_block(STRING("/index.html"), DEFAULT_GLOBAL_ATTRIBUTES) { pgprint_string(STRING("Home")); } }
			pgprint_li_element_block(DEFAULT_GLOBAL_ATTRIBUTES) {
				pgprint_a_element_block(STRING("/games.html"), DEFAULT_GLOBAL_ATTRIBUTES) { pgprint_string(STRING("Portfolio")); } }
			// pgprint_li_element_block(DEFAULT_GLOBAL_ATTRIBUTES) {
			// 	pgprint_a_element_block(STRING("/other.html"), DEFAULT_GLOBAL_ATTRIBUTES) { pgprint_string(STRING("Other")); } }
			// pgprint_li_element_block(DEFAULT_GLOBAL_ATTRIBUTES) {
			// 	pgprint_a_element_block(STRING("blog.html"), DEFAULT_GLOBAL_ATTRIBUTES) { pgprint_string(STRING("Blog")); } }
		}
		// pgprint_hr_element();
		pgprint_nav_element_block((Global_Attributes){ .class = STRING("my-nav") }) {
		} } }

int main(int argc, char* argv[]) {
	generator = calloc(1, sizeof(Generator));
	begin(generator);

	//////////////////////////
	// INTRO PAGE
	//
	HTML_File intro_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/intro.typ")), HTML_ELEMENT_BODY);
	const String index_page_name = COMPTIME_STRING("docs\\index");
	pgprint_page_block(index_page_name) {
		pgprint_html_element_block(STRING("en")) {
			pgprint_head();
			pgprint_body_element_block(GLOBAL_ATTRIBUTES(.class = STRING("my-body"))) {
				pgprint_header(STRING("Nikola Stefanov"));
				pgprint_string(html_file_to_string(intro_file));
				pgprint_footer_element_block(DEFAULT_GLOBAL_ATTRIBUTES) { }
			}
		}
	}

	//////////////////////////
	// GAMES PAGE
	//
	// HTML_File game_soap_glider_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/game-soap-glider.typ")), HTML_ELEMENT_BODY);
	// HTML_File game_the_blue_break_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/game-blue-break.typ")), HTML_ELEMENT_BODY);
	// HTML_File game_bribe_artist_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/game-bribe-artist.typ")), HTML_ELEMENT_BODY);
	// HTML_File game_wanda_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/game-wanda.typ")), HTML_ELEMENT_BODY);
	// HTML_File game_bogwalker_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/game-bogwalker.typ")), HTML_ELEMENT_BODY);
	// HTML_File game_royal_dispute_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/game-royal-dispute.typ")), HTML_ELEMENT_BODY);
	const String games_page_name = COMPTIME_STRING("docs\\games");
	pgprint_page_block(games_page_name) {
		pgprint_html_element_block(STRING("en")) {
			pgprint_head();
			pgprint_body_element_block((Global_Attributes){ .class = STRING("my-body") }) {
				pgprint_header(STRING("Portfolio"));
				// royal-dispute-thumbnail
				GRID_CONTAINER() {
					GRID_ITEM("Soap Glider", "/soap-glider.html", "soap-glider-thumbnail.png")
					GRID_ITEM("Royal Dispute", "/royal-dispute.html", "royal-dispute-thumbnail.png")
					GRID_ITEM("The Blue Break", "/the-blue-break.html", "the-blue-break-thumbnail.png")
					GRID_ITEM("Bribe Artist", "/bribe-artist.html", "bribe-artist-thumbnail.png")
					GRID_ITEM("Wanda", "/wanda.html", "wanda-thumbnail.png")
					GRID_ITEM("Bogwalker", "/bogwalker.html", "bogwalker-thumbnail.png")
					GRID_ITEM("Blade and Eye", "/blade-and-eye.html", "blade-and-eye-thumbnail.png")
				}
				// pgprint_h2_element(STRING("Soap Glider"), GLOBAL_ATTRIBUTES(.id = STRING("soap-glider")));
				// pgprint_string(html_file_to_string(game_soap_glider_file));
				// pgprint_hr_element();
				// pgprint_h2_element(STRING("The Blue Break"), GLOBAL_ATTRIBUTES(.id = STRING("the-blue-break")));
				// pgprint_string(html_file_to_string(game_the_blue_break_file));
				// pgprint_hr_element();
				// pgprint_h2_element(STRING("Royal Dispute"), GLOBAL_ATTRIBUTES(.id = STRING("royal-dispute")));
				// pgprint_string(html_file_to_string(game_royal_dispute_file));
				// pgprint_hr_element();
				// pgprint_h2_element(STRING("Bribe Artist"), GLOBAL_ATTRIBUTES(.id = STRING("bribe-artist")));
				// pgprint_string(html_file_to_string(game_bribe_artist_file));
				// pgprint_hr_element();
				// pgprint_h2_element(STRING("Wanda"), GLOBAL_ATTRIBUTES(.id = STRING("wanda")));
				// pgprint_string(html_file_to_string(game_wanda_file));
				// pgprint_hr_element();
				// pgprint_h2_element(STRING("Bogwalker"), GLOBAL_ATTRIBUTES(.id = STRING("bogwalker")));
				// pgprint_string(html_file_to_string(game_bogwalker_file));
			}
		}
	}

	//////////////////////////
	// OTHER PAGE
	//
	HTML_File other_gasbol_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/other-gasbol.typ")), HTML_ELEMENT_BODY);
	const String other_page_name = COMPTIME_STRING("docs\\other");
	pgprint_page_block(other_page_name) {
		pgprint_html_element_block(STRING("en")) {
			pgprint_head();
			pgprint_body_element_block((Global_Attributes){ .class = STRING("my-body") }) {
				pgprint_header(STRING("Other"));
				pgprint_string(html_file_to_string(other_gasbol_file));
			}
		}
	}

	//////////////////////////
	// BLOG PAGE
	//
	const String blog_page_name = COMPTIME_STRING("docs\\blog");
	pgprint_page_block(blog_page_name) {
		pgprint_html_element_block(STRING("en")) {
			pgprint_head();
			pgprint_body_element_block((Global_Attributes){ .class = STRING("my-body") }) {
				pgprint_header(STRING("Blog"));
			}
		}
	}

	//////////////////////////
	// SOAP GLIDER PAGE
	//
	HTML_File soap_glider_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/soap-glider.typ")), HTML_ELEMENT_BODY);
	const String soap_glider_page_name = COMPTIME_STRING("docs\\soap-glider");
	pgprint_page_block(soap_glider_page_name) {
		pgprint_html_element_block(STRING("en")) {
			pgprint_head();
			pgprint_body_element_block((Global_Attributes){ .class = STRING("my-body") }) {
				pgprint_header(STRING("Soap Glider"));
				pgprint_string(html_file_to_string(soap_glider_file));
				pgprint_footer_element_block(DEFAULT_GLOBAL_ATTRIBUTES) { }
			}
		}
	}

	//////////////////////////
	// ROYAL DISPUTE PAGE
	//
	HTML_File royal_dispute_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/royal-dispute.typ")), HTML_ELEMENT_BODY);
	const String royal_dispute_page_name = COMPTIME_STRING("docs\\royal-dispute");
	pgprint_page_block(royal_dispute_page_name) {
		pgprint_html_element_block(STRING("en")) {
			pgprint_head();
			pgprint_body_element_block((Global_Attributes){ .class = STRING("my-body") }) {
				pgprint_header(STRING("Royal Dispute"));
				pgprint_string(html_file_to_string(royal_dispute_file));
				pgprint_footer_element_block(DEFAULT_GLOBAL_ATTRIBUTES) { }
			}
		}
	}

	//////////////////////////
	// BRIBE ARTIST PAGE
	//
	HTML_File bribe_artist_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/bribe-artist.typ")), HTML_ELEMENT_BODY);
	const String bribe_artist_page_name = COMPTIME_STRING("docs\\bribe-artist");
	pgprint_page_block(bribe_artist_page_name) {
		pgprint_html_element_block(STRING("en")) {
			pgprint_head();
			pgprint_body_element_block((Global_Attributes){ .class = STRING("my-body") }) {
				pgprint_header(STRING("Bribe Artist"));
				pgprint_string(html_file_to_string(bribe_artist_file));
				pgprint_footer_element_block(DEFAULT_GLOBAL_ATTRIBUTES) { }
			}
		}
	}

	//////////////////////////
	// THE BLUE BREAK PAGE
	//
	HTML_File the_blue_break_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/the-blue-break.typ")), HTML_ELEMENT_BODY);
	const String the_blue_break_page_name = COMPTIME_STRING("docs\\the-blue-break");
	pgprint_page_block(the_blue_break_page_name) {
		pgprint_html_element_block(STRING("en")) {
			pgprint_head();
			pgprint_body_element_block((Global_Attributes){ .class = STRING("my-body") }) {
				pgprint_header(STRING("The Blue Break"));
				pgprint_string(html_file_to_string(the_blue_break_file));
				pgprint_footer_element_block(DEFAULT_GLOBAL_ATTRIBUTES) { }
			}
		}
	}

	//////////////////////////
	// WANDA PAGE
	//
	HTML_File wanda_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/wanda.typ")), HTML_ELEMENT_BODY);
	const String wanda_page_name = COMPTIME_STRING("docs\\wanda");
	pgprint_page_block(wanda_page_name) {
		pgprint_html_element_block(STRING("en")) {
			pgprint_head();
			pgprint_body_element_block((Global_Attributes){ .class = STRING("my-body") }) {
				pgprint_header(STRING("Wanda"));
				pgprint_string(html_file_to_string(wanda_file));
				pgprint_footer_element_block(DEFAULT_GLOBAL_ATTRIBUTES) { }
			}
		}
	}

	//////////////////////////
	// BOGWALKER PAGE
	//
	HTML_File bogwalker_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/bogwalker.typ")), HTML_ELEMENT_BODY);
	const String bogwalker_page_name = COMPTIME_STRING("docs\\bogwalker");
	pgprint_page_block(bogwalker_page_name) {
		pgprint_html_element_block(STRING("en")) {
			pgprint_head();
			pgprint_body_element_block((Global_Attributes){ .class = STRING("my-body") }) {
				pgprint_header(STRING("Bogwalker"));
				pgprint_string(html_file_to_string(bogwalker_file));
				pgprint_footer_element_block(DEFAULT_GLOBAL_ATTRIBUTES) { }
			}
		}
	}

	//////////////////////////
	// BLADE & EYE PAGE
	//
	HTML_File blade_and_eye_file = html_file_search_element_depth_first(html_file_from_typst(STRING("source/content/blade-and-eye.typ")), HTML_ELEMENT_BODY);
	const String blade_and_eye_page_name = COMPTIME_STRING("docs\\blade-and-eye");
	pgprint_page_block(blade_and_eye_page_name) {
		pgprint_html_element_block(STRING("en")) {
			pgprint_head();
			pgprint_body_element_block((Global_Attributes){ .class = STRING("my-body") }) {
				pgprint_header(STRING("Blade and Eye"));
				pgprint_string(html_file_to_string(blade_and_eye_file));
				pgprint_footer_element_block(DEFAULT_GLOBAL_ATTRIBUTES) { }
			}
		}
	}

	//////////////////////////
	// STYLE
	//
	const String style_name = COMPTIME_STRING("docs\\style");
	pgprint_style_block(style_name) {
		pgprint_charset_atrule(STRING("utf-8"));
		pgprint_font_face_atrule(STRING("Radley Regular"), STRING("Radley-Regular.ttf"));
		pgprint_font_face_atrule(STRING("Goudy Bookletter 1911 Regular"), STRING("GoudyBookletter1911-Regular.ttf"));
		pgprint_font_face_atrule(STRING("Sorts Mill Goudy Regular"), STRING("SortsMillGoudy-Regular.ttf"));
		pgprint_font_face_atrule(STRING("Crimson Text Regular"), STRING("CrimsonText-Regular.ttf"));
		pgprint_font_face_atrule(STRING("EB Garamond Regular"), STRING("EBGaramond-Medium.ttf"));
		pgprint_font_face_atrule(STRING("Trocchi Regular"), STRING("Trocchi-Regular.ttf"));
		pgprint_font_face_atrule(STRING("Jersey10 Regular"), STRING("Jersey10-Regular.ttf"));
		pgprint_generic_rule_block(STRING("html")) {
			pgprint_generic_declaration(STRING("font-family"), STRING("\"Trocchi Regular\""));
			pgprint_generic_declaration(STRING("font-size"), STRING("1.5vh"));
			pgprint_generic_declaration(STRING("color"), COLOR_FOREGROUND_STRING);
			pgprint_generic_declaration(STRING("background-color"), COLOR_BACKGROUND_STRING);
			pgprint_generic_declaration(STRING("text-rendering"), STRING("optimizeLegibility"));
			pgprint_generic_declaration(STRING("word-spacing"), STRING("0.1em"));
			pgprint_generic_declaration(STRING("font-feature-settings"), STRING("'kern', 'liga', 'cpsp' on"));
		}
		pgprint_generic_rule_block(STRING("body")) {
			pgprint_generic_declaration(STRING("width"), STRING("auto"));
			pgprint_generic_declaration(STRING("margin-inline"), STRING("calc(max((100vw - 800px) / 2, 5vw))"));
			pgprint_generic_declaration(STRING("margin-bottom"), STRING("50vh"));
		}
		pgprint_generic_rule_block(STRING("h1")) {
			pgprint_generic_declaration(STRING("font-size"), STRING("4.8vh"));
			pgprint_generic_declaration(STRING("font-family"), STRING("\"Trocchi Regular\""));
			// pgprint_generic_declaration(STRING("font-family"), STRING("\"Jersey10 Regular\""));
			pgprint_generic_declaration(STRING("font-weight"), STRING("800"));
		}
		pgprint_generic_rule_block(STRING("h2")) {
			pgprint_generic_declaration(STRING("font-size"), STRING("3.4vh"));
			// pgprint_generic_declaration(STRING("font-family"), STRING("\"Jersey10 Regular\""));
			// pgprint_generic_declaration(STRING("font-weight"), STRING("100"));
		}
		pgprint_generic_rule_block(STRING("hr")) {
			pgprint_generic_declaration(STRING("color"), COLOR_FOREGROUND_STRING);
			pgprint_generic_declaration(STRING("border-top"), STROKE);
			pgprint_generic_declaration(STRING("border-bottom"), STRING("5px solid #d6d5eb"));
		}
		pgprint_generic_rule_block(STRING("img, video")) {
			pgprint_generic_declaration(STRING("image-rendering"), STRING("pixelated"));
			pgprint_generic_declaration(STRING("border"), STROKE);
			pgprint_generic_declaration(STRING("box-shadow"), SHADOW);
			pgprint_generic_declaration(STRING("width"), STRING("100%"));
			pgprint_generic_declaration(STRING("height"), STRING("auto"));
			pgprint_generic_declaration(STRING("display"), STRING("block"));
			pgprint_generic_declaration(STRING("position"), STRING("relative"));
			pgprint_generic_declaration(STRING("z-index"), STRING("2000"));
		}
		pgprint_generic_rule_block(STRING(".selfie")) {
			pgprint_generic_declaration(STRING("border"), STROKE);
			pgprint_generic_declaration(STRING("width"), STRING("33.3333%"));
			pgprint_generic_declaration(STRING("border-radius"), STRING("0%"));
		}
		pgprint_generic_rule_block(STRING("a:link, a:visited")) {
			pgprint_generic_declaration(STRING("color"), STRING("#585cdf"));
		}
		pgprint_generic_rule_block(STRING("a:hover")) {
			pgprint_generic_declaration(STRING("color"), STRING("#4907FF"));
		}
		pgprint_generic_rule_block(STRING("ul")) {
			pgprint_generic_declaration(STRING("list-style-type"), STRING("none"));
			pgprint_generic_declaration(STRING("padding"), STRING("0"));
			pgprint_generic_declaration(STRING("overflow"), STRING("hidden"));
			pgprint_generic_declaration(STRING("margin"), STRING("0"));
			pgprint_generic_declaration(STRING("margin-bottom"), STRING("1em"));
		}
		pgprint_generic_rule_block(STRING("li")) {
			pgprint_generic_declaration(STRING("float"), STRING("left"));
			pgprint_generic_declaration(STRING("padding-right"), STRING("10pt"));
		}
		pgprint_generic_rule_block(STRING(".overlay")) {
			pgprint_generic_declaration(STRING("background-image"), STRING("url('overlay.png')"));
			pgprint_generic_declaration(STRING("position"), STRING("fixed"));
			pgprint_generic_declaration(STRING("inset"), STRING("0"));
			pgprint_generic_declaration(STRING("pointer-events"), STRING("none"));
			pgprint_generic_declaration(STRING("z-index"), STRING("1000"));
			pgprint_generic_declaration(STRING("background-repeat"), STRING("repeat"));
			pgprint_generic_declaration(STRING("background-size"), STRING("auto"));
			pgprint_generic_declaration(STRING("background-position"), STRING("0 0"));
			pgprint_generic_declaration(STRING("mix-blend-mode"), STRING("overlay"));
			pgprint_generic_declaration(STRING("opacity"), STRING("0.5"));
		}
		pgprint_generic_rule_block(STRING(".grid-container")) {
			pgprint_generic_declaration(STRING("display"), STRING("grid"));
			pgprint_generic_declaration(STRING("grid-template-columns"), STRING("auto auto auto"));
			pgprint_generic_declaration(STRING("grid-gap"), STRING("1px"));
			pgprint_generic_declaration(STRING("padding"), STRING("0px"));
		}
		pgprint_generic_rule_block(STRING(".grid-item")) {
			pgprint_generic_declaration(STRING("position"), STRING("relative"));
		}
		pgprint_generic_rule_block(STRING(".caption")) {
			pgprint_generic_declaration(STRING("position"), STRING("absolute"));
			pgprint_generic_declaration(STRING("bottom"), STRING("5%"));
			pgprint_generic_declaration(STRING("left"), STRING("5%"));
			pgprint_generic_declaration(STRING("right"), STRING("5%"));
			pgprint_generic_declaration(STRING("background-color"), STRING("rgba(0, 0, 0, 1)"));
			pgprint_generic_declaration(STRING("color"), STRING("white"));
			pgprint_generic_declaration(STRING("text-align"), STRING("center"));
			pgprint_generic_declaration(STRING("padding"), STRING("0.5em"));
			pgprint_generic_declaration(STRING("box-shadow"), STRING("5px 5px rgba(0, 0, 0, 0.15)"));
			pgprint_generic_declaration(STRING("z-index"), STRING("3000"));
			pgprint_generic_declaration(STRING("opacity"), STRING("0"));
			pgprint_generic_declaration(STRING("transition"), STRING("opacity 0.2s ease"));
		}
		pgprint_generic_rule_block(STRING(".grid-item:hover .caption")) {
			pgprint_generic_declaration(STRING("opacity"), STRING("1"));
		}
	}
	return 0; }
