#include "leptjson.h"

int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    return lept_parse_value(&c, v);
}


#define EXPECT(c, ch) do {assert(*c->json == (ch)); c->json++;} while(0)

static void lept_parse_whitespace(lept_context* c) {
    const char* p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p = '\r')
        p++;
    c->json;
}


static void lept_parse_null(lept_context* c, lept_value* v) {
    EXPECT(c, 'n')
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l') {
        return LEPT_PARSE_INVALID_VALUE;
    }

    c->json += 3;
    v->type = LEPT_NULL;
    return LETP_PARSE_OK;
}

