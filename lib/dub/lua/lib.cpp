/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for library {{lib_name}}
 *
 * This file has been generated by dub {{dub.VERSION}}.
 */
#include "dub/dub.h"
{% for h in self:headers() do %}
#include "{{self:header(h)}}"
{% end %}

{% for namespace in lib:namespaces() do %}
using namespace {{namespace.name}};
{% end %}

extern "C" {
{% for _, class in ipairs(classes) do %}
int luaopen_{{self:openName(class)}}(lua_State *L);
{% end %}
}

{% for method in lib:functions() do %}
/** {{method:nameWithArgs()}}
 * {{method.location}}
 */
static int {{string.gsub(method:fullcname(), '::', '_')}}(lua_State *L) {
{% if method:neverThrows() then %}

  {| self:functionBody(method) |}
{% else %}
  try {
    {| self:functionBody(method) |}
  } catch (std::exception &e) {
    lua_pushfstring(L, "{{self:libName(method)}}: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "{{self:libName(method)}}: Unknown exception");
  }
  return lua_error(L);
{% end %}
}

{% end %}
// --=============================================== FUNCTIONS

static const struct luaL_Reg {{lib_name}}_functions[] = {
{% for method in lib:functions() do %}
  { {{string.format('%-15s, %-20s', '"'..self:bindName(method)..'"', string.gsub(method:fullcname(), '::', '_'))}} },
{% end %}
  { NULL, NULL},
};

{% if lib.has_constants then %}
// --=============================================== CONSTANTS
static const struct dub_const_Reg {{lib_name}}_const[] = {
{% for const in lib:constants() do %}
  { {{string.format('%-15s, %-20s', '"'.. self:constName(const) ..'"', const)}} },
{% end %}
  { NULL, 0},
};
{% end %}

extern "C" int luaopen_{{lib_name}}(lua_State *L) {
{% for _, class in ipairs(classes) do %}
  luaopen_{{self:openName(class)}}(L);
{% end %}

{% if lib.has_constants or #lib.functions_list > 0 then %}
  // Create the table which will contain all the constants
  lua_getfield(L, LUA_GLOBALSINDEX, "{{lib_name}}");
  if (lua_isnil(L, -1)) {
    // no global table called {{lib_name}}
    lua_pop(L, 1);
    lua_newtable(L);
    // <lib>
    lua_pushvalue(L, -1);
    // <lib> <lib>
    // _G.{{lib_name}} = <lib>
    lua_setglobal(L, "{{lib_name}}");
    // <lib>
  }
  // <lib>
{% end %}
{% if lib.has_constants then %}
  // register global constants
  dub_register_const(L, {{lib_name}}_const);
{% end %}
  luaL_register(L, NULL, {{lib_name}}_functions);
  // <lib>
  lua_pop(L, 1);
  return 0;
}
