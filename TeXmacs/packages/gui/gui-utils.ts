<TeXmacs|1.0.6.8>

<style|source>

<\body>
  <active*|<\src-title>
    <src-package|gui-utils|1.0>

    <\src-purpose>
      Standard GUI utilities
    </src-purpose>

    <src-copyright|2007|Joris van der Hoeven>

    <\src-license>
      This <TeXmacs> style package falls under the <hlink|GNU general public
      license|$TEXMACS_PATH/LICENSE> and comes WITHOUT ANY WARRANTY
      WHATSOEVER. If you don't have this file, then write to the Free
      Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
      02111-1307, USA.
    </src-license>
  </src-title>>

  <assign|bg-color|light grey>

  <assign|page-medium|automatic>

  <assign|scroll-bars|false>

  <assign|font-family|ss>

  <assign|par-sep|0.2em>

  <assign|par-par-sep|0em>

  <assign|par-line-sep|0em>

  <assign|page-screen-left|0.5em>

  <assign|page-screen-right|0.5em>

  <assign|page-screen-top|0.5em>

  <assign|page-screen-bot|0.5em>

  <\active*>
    <\src-comment>
      Gui environment variables
    </src-comment>
  </active*>

  <assign|gui-small-sep|0.25em>

  <assign|gui-med-sep|0.5em>

  <assign|gui-big-sep|1em>

  <assign|raised-color|light grey>

  <assign|lowered-color|#e0e0e0>

  <assign|bright-color|#f0f0f0>

  <assign|sunny-color|white>

  <assign|shadow-color|grey>

  <assign|button-shape|square>

  <assign|box-shape|circular>

  <assign|box-color|pastel blue>

  <assign|marker-shape|checked>

  <\active*>
    <\src-comment>
      Submacros for form identifiers
    </src-comment>
  </active*>

  <drd-props|form-window|arity|<tuple|repeat|1|1>|border|no>

  <assign|form-prefix|>

  <assign|form|<macro|name|body|<style-with|src-compact|none|<with|form-prefix|<merge|<value|form-prefix>|<arg|name>|->|<wide-normal|<arg|body>>>>>>

  <assign|form-id|<macro|name|<id|<merge|<value|form-prefix>|<arg|name>>>>>

  <assign|form-value|<macro|name|<extern|widget-ref|<arg|name>|<value|form-prefix>>>>

  <assign|form-cmd|<macro|cmd|<merge|(widget-delay (widget-with
  "|<value|form-prefix>|" |<arg|cmd>|))>>>

  <\active*>
    <\src-comment>
      Tables
    </src-comment>
  </active*>

  <assign|dense-raster|<macro|body|<tformat|<twith|table-valign|C>|<twith|table-width|1par>|<twith|table-hmode|exact>|<cwith|1|-1|1|-1|cell-vcorrect|n>|<cwith|1|-1|1|-1|cell-hyphen|t>|<cwith|1|-1|1|-1|cell-lsep|0px>|<cwith|1|-1|1|-1|cell-rsep|0px>|<cwith|-1|1|1|-1|cell-tsep|0px>|<cwith|1|-1|1|-1|cell-bsep|0px>|<arg|body>>>>

  <assign|short-raster|<macro|body|<tformat|<twith|table-valign|C>|<cwith|1|-1|1|-1|cell-vcorrect|n>|<cwith|1|-1|1|1|cell-lsep|0px>|<cwith|1|-1|2|-1|cell-lsep|<value|gui-med-sep>>|<cwith|1|-1|1|-1|cell-rsep|0px>|<cwith|-1|1|1|-1|cell-tsep|0px>|<cwith|1|-1|1|-1|cell-bsep|0px>|<arg|body>>>>

  <assign|wide-raster|<macro|body|<tformat|<twith|table-valign|C>|<twith|table-width|1par>|<twith|table-hmode|exact>|<cwith|1|-1|1|-1|cell-vcorrect|n>|<cwith|1|-1|1|-1|cell-hyphen|t>|<cwith|1|-1|1|1|cell-lsep|0px>|<cwith|1|-1|2|-1|cell-lsep|<value|gui-med-sep>>|<cwith|1|-1|1|-1|cell-rsep|0px>|<cwith|1|1|1|-1|cell-tsep|0px>|<cwith|2|-1|1|-1|cell-tsep|<value|gui-med-sep>>|<cwith|1|-1|1|-1|cell-bsep|0px>|<arg|body>>>>

  <\active*>
    <\src-comment>
      Framed boxes
    </src-comment>
  </active*>

  <assign|short-highlight|<macro|main-col|border1-col|border2-col|pad|body|<dense-raster|<tformat|<twith|table-hmode|auto>|<cwith|1|1|1|-1|cell-background|<arg|border1-col>>|<cwith|3|3|1|-1|cell-background|<arg|border2-col>>|<cwith|1|-1|3|3|cell-background|<arg|border2-col>>|<cwith|1|-1|1|1|cell-background|<arg|border1-col>>|<cwith|1|-1|1|1|cell-width|1px>|<cwith|1|-1|1|1|cell-hmode|exact>|<cwith|1|-1|3|3|cell-width|1px>|<cwith|1|-1|3|3|cell-hmode|exact>|<cwith|1|1|1|-1|cell-height|1px>|<cwith|1|1|1|-1|cell-vmode|exact>|<cwith|3|3|1|-1|cell-height|1px>|<cwith|3|3|1|-1|cell-vmode|exact>|<cwith|2|2|2|2|cell-lsep|<arg|pad>>|<cwith|2|2|2|2|cell-rsep|<arg|pad>>|<cwith|2|2|2|2|cell-bsep|<arg|pad>>|<cwith|2|2|2|2|cell-tsep|<arg|pad>>|<cwith|2|2|2|2|cell-vcorrect|a>|<cwith|2|2|2|2|cell-hyphen|n>|<cwith|2|2|2|2|cell-hpart|1>|<table|<row|<cell|>|<cell|>|<cell|>>|<row|<cell|>|<cell|<arg|body>>|<cell|>>|<row|<cell|>|<cell|>|<cell|>>>>>>>

  <assign|wide-highlight|<macro|main-col|border1-col|border2-col|pad|body|<dense-raster|<tformat|<cwith|1|1|1|-1|cell-background|<arg|border1-col>>|<cwith|3|3|1|-1|cell-background|<arg|border2-col>>|<cwith|1|-1|1|1|cell-background|<arg|border1-col>>|<cwith|1|-1|1|1|cell-width|1px>|<cwith|1|-1|1|1|cell-hmode|exact>|<cwith|1|1|1|-1|cell-height|1px>|<cwith|1|1|1|-1|cell-vmode|exact>|<cwith|3|3|1|-1|cell-height|1px>|<cwith|3|3|1|-1|cell-vmode|exact>|<cwith|2|2|2|2|cell-background|<arg|main-col>>|<cwith|2|2|2|2|cell-lsep|<arg|pad>>|<cwith|2|2|2|2|cell-rsep|<arg|pad>>|<cwith|2|2|2|2|cell-bsep|<arg|pad>>|<cwith|2|2|2|2|cell-tsep|<arg|pad>>|<cwith|2|2|2|2|cell-vcorrect|a>|<cwith|2|2|2|2|cell-hyphen|n>|<cwith|2|2|2|2|cell-hpart|1>|<table|<row|<cell|>|<cell|>|<cell|>>|<row|<cell|>|<cell|<arg|body>>|<cell|>>|<row|<cell|>|<cell|>|<cell|>>>>>>>

  <assign|block-highlight|<macro|main-col|border1-col|border2-col|pad|body|<dense-raster|<tformat|<cwith|1|1|1|-1|cell-background|<arg|border1-col>>|<cwith|3|3|1|-1|cell-background|<arg|border2-col>>|<cwith|1|-1|3|3|cell-background|<arg|border2-col>>|<cwith|1|-1|1|1|cell-background|<arg|border1-col>>|<cwith|1|-1|1|1|cell-width|1px>|<cwith|1|-1|1|1|cell-hmode|exact>|<cwith|1|-1|3|3|cell-width|1px>|<cwith|1|-1|3|3|cell-hmode|exact>|<cwith|1|1|1|-1|cell-height|1px>|<cwith|1|1|1|-1|cell-vmode|exact>|<cwith|3|3|1|-1|cell-height|1px>|<cwith|3|3|1|-1|cell-vmode|exact>|<cwith|2|2|2|2|cell-background|<arg|main-col>>|<cwith|2|2|2|2|cell-lsep|<arg|pad>>|<cwith|2|2|2|2|cell-rsep|<arg|pad>>|<cwith|2|2|2|2|cell-bsep|<arg|pad>>|<cwith|2|2|2|2|cell-tsep|<arg|pad>>|<table|<row|<cell|>|<cell|>|<cell|>>|<row|<cell|>|<\cell>
    <arg|body>
  </cell>|<cell|>>|<row|<cell|>|<cell|>|<cell|>>>>>>>

  \;

  <assign|short-raise|<style-with|src-compact|none|<macro|body|<short-highlight|<value|raised-color>|<value|sunny-color>|<value|shadow-color>|<value|gui-small-sep>|<arg|body>>>>>

  <assign|short-lower|<style-with|src-compact|none|<macro|body|<short-highlight|<value|lowered-color>|<value|shadow-color>|<value|sunny-color>|<value|gui-small-sep>|<arg|body>>>>>

  <assign|short-bright|<style-with|src-compact|none|<macro|body|<short-highlight|<value|bright-color>|<value|shadow-color>|<value|sunny-color>|<value|gui-small-sep>|<arg|body>>>>>

  <assign|wide-raise|<style-with|src-compact|none|<macro|body|<wide-highlight|<value|raised-color>|<value|sunny-color>|<value|shadow-color>|<value|gui-small-sep>|<arg|body>>>>>

  <assign|wide-lower|<style-with|src-compact|none|<macro|body|<wide-highlight|<value|lowered-color>|<value|shadow-color>|<value|sunny-color>|<value|gui-small-sep>|<arg|body>>>>>

  <assign|wide-bright|<style-with|src-compact|none|<macro|body|<wide-highlight|<value|bright-color>|<value|shadow-color>|<value|sunny-color>|<value|gui-small-sep>|<arg|body>>>>>

  <assign|block-raise|<style-with|src-compact|none|<macro|body|<block-highlight|<value|raised-color>|<value|sunny-color>|<value|shadow-color>|<value|gui-med-sep>|<arg|body>>>>>

  <assign|block-lower|<style-with|src-compact|none|<macro|body|<block-highlight|<value|lowered-color>|<value|shadow-color>|<value|sunny-color>|<value|gui-med-sep>|<arg|body>>>>>

  <assign|block-bright|<style-with|src-compact|none|<macro|body|<block-highlight|<value|bright-color>|<value|shadow-color>|<value|sunny-color>|<value|gui-med-sep>|<arg|body>>>>>

  <\active*>
    <\src-comment>
      Input fields
    </src-comment>
  </active*>

  <assign|short-input|<macro|name|val|<short-bright|<locus|<form-id|<arg|name>>|<arg|val>>>>>

  <assign|wide-input|<macro|name|val|<wide-bright|<locus|<form-id|<arg|name>>|<arg|val>>>>>

  <assign|block-input|<\macro|name|val>
    <\block-bright>
      <\locus|<form-id|<arg|name>>>
        <arg|val>
      </locus>
    </block-bright>
  </macro>>

  <assign|hidden-input|<macro|name|val|body|<surround|<hidden|<locus|<form-id|<arg|name>>|<arg|val>>>||<with|<merge|form-value-|<arg|name>>|<arg|val>|<arg|body>>>>>

  <\active*>
    <\src-comment>
      Spacing markup for graphical user interfaces
    </src-comment>
  </active*>

  <assign|gui-ruler|<macro|around|left|right|height|col|<dense-raster|<tformat|<cwith|1|-1|1|-1|cell-vmode|exact>|<cwith|1|1|1|-1|cell-height|<arg|around>>|<cwith|2|2|1|-1|cell-height|1px>|<cwith|3|3|1|-1|cell-height|<arg|height>>|<cwith|4|4|1|-1|cell-height|1px>|<cwith|5|5|1|-1|cell-height|<arg|around>>|<cwith|2|2|1|-1|cell-background|<value|shadow-color>>|<cwith|4|4|1|-1|cell-background|<value|sunny-color>>|<cwith|3|3|1|1|cell-background|<value|shadow-color>>|<cwith|3|3|2|2|cell-background|<arg|col>>|<cwith|3|3|3|3|cell-background|<value|sunny-color>>|<cwith|1|-1|1|1|cell-width|<arg|left>>|<cwith|1|-1|1|1|cell-hmode|exact>|<cwith|1|-1|3|3|cell-width|<arg|right>>|<cwith|1|-1|3|3|cell-hmode|exact>|<cwith|1|-1|2|2|cell-hpart|1>|<table|<row|<cell|>|<cell|>|<cell|>>|<row|<cell|>|<cell|>|<cell|>>|<row|<cell|>|<cell|>|<cell|>>|<row|<cell|>|<cell|>|<cell|>>|<row|<cell|>|<cell|>|<cell|>>>>>>>

  <assign|gui-vspace|<macro|height|<dense-raster|<tformat|<cwith|1|-1|1|1|cell-vmode|exact>|<cwith|1|1|1|1|cell-height|<arg|height>>|<table|<row|<cell|>>>>>>>

  <assign|gui-hrule|<macro|<gui-ruler|<value|gui-med-sep>|0px|0px|0px|<value|lowered-color>>>>

  <assign|gui-medskip|<macro|<gui-vspace|<value|gui-med-sep>>>>

  <assign|gui-tab|<macro|<tabular|<tformat|<twith|table-width|1par>|<twith|table-hmode|exact>|<cwith|1|1|1|1|cell-lsep|0px>|<cwith|1|1|1|1|cell-rsep|0px>|<cwith|1|1|1|1|cell-bsep|0px>|<cwith|1|1|1|1|cell-tsep|0px>|<cwith|1|1|1|1|cell-hyphen|t>|<cwith|1|1|1|1|cell-vcorrect|n>|<table|<row|<\cell>
    \;
  </cell>>>>>>>

  <\active*>
    <\src-comment>
      Widget headers
    </src-comment>
  </active*>

  <assign|header-bar-sub|<macro|l|c|r|<dense-raster|<tformat|<cwith|1|-1|1|-1|cell-hyphen|n>|<cwith|1|1|1|1|cell-hpart|1>|<cwith|1|1|3|3|cell-hpart|1>|<cwith|1|1|3|3|cell-halign|r>|<cwith|1|1|2|2|cell-halign|c>|<cwith|1|1|1|1|cell-halign|l>|<cwith|1|1|1|1|cell-hyphen|t>|<cwith|1|1|3|3|cell-hyphen|t>|<cwith|1|1|2|2|cell-width|>|<cwith|1|1|2|2|cell-hmode|auto>|<table|<row|<\cell>
    <arg|l>
  </cell>|<cell|<arg|c>>|<\cell>
    <arg|r>
  </cell>>>>>>>

  <assign|header-bar|<macro|body|<style-with|src-compact|none|<header-bar-sub|<gui-ruler|0px|1px|0px|5px|<value|lowered-color>>|<arg|body>|<gui-ruler|0px|0px|1px|5px|<value|lowered-color>>>>>>

  <\active*>
    <\src-comment>
      Buttons
    </src-comment>
  </active*>

  <assign|invisible-button|<macro|on|body|<group|<arg|body>>>>

  <assign|square-button|<macro|on|body|<style-with|src-compact|none|<if|<equal|<arg|on>|true>|<short-lower|<arg|body>>|<short-raise|<arg|body>>>>>>

  <assign|render-button|<macro|on|body|<compound|<merge|<value|button-shape>|-button>|<arg|on>|<arg|body>>>>

  <assign|button|<macro|body|cmd|<render-button|false|<action|<arg|body>|<form-cmd|<arg|cmd>>|<arg|body>>>>>

  <\active*>
    <\src-comment>
      Boxes
    </src-comment>
  </active*>

  <assign|magnify|<macro|factor|body|<with|magnification|<times|<value|magnification>|<arg|factor>>|<arg|body>>>>

  <assign|gui-centered-cell|<macro|body|<tabular|<tformat|<cwith|1|1|1|1|cell-halign|c>|<cwith|1|1|1|1|cell-valign|c>|<cwith|1|1|1|1|cell-width|1em>|<cwith|1|1|1|1|cell-hmode|exact>|<cwith|1|1|1|1|cell-height|1em>|<cwith|1|1|1|1|cell-vmode|exact>|<cwith|1|1|1|1|cell-vcorrect|n>|<cwith|1|1|1|1|cell-lsep|0em>|<cwith|1|1|1|1|cell-rsep|0em>|<cwith|1|1|1|1|cell-bsep|0em>|<cwith|1|1|1|1|cell-tsep|0em>|<table|<row|<cell|<arg|body>>>>>>>>

  <assign|circular-box|<macro|body|<style-with|src-compact|none|<superpose|<gui-centered-cell|<magnify|2.5|<style-with|src-compact|none|<move|<with|bg-color|<value|color>|<with|mode|math|color|<value|box-color>|\<bullet\>>>|0.02em|-0.055em>>>>|<gui-centered-cell|<magnify|1.1|<with|mode|math|\<bigcirc\>>>>|<gui-centered-cell|<arg|body>>>>>>

  <assign|square-box|<macro|body|<tabular|<tformat|<cwith|1|1|1|1|cell-halign|c>|<cwith|1|1|1|1|cell-valign|c>|<cwith|1|1|1|1|cell-width|0.9em>|<cwith|1|1|1|1|cell-hmode|exact>|<cwith|1|1|1|1|cell-height|0.9em>|<cwith|1|1|1|1|cell-vmode|exact>|<cwith|1|1|1|1|cell-vcorrect|n>|<cwith|1|1|1|1|cell-lsep|0em>|<cwith|1|1|1|1|cell-rsep|0em>|<cwith|1|1|1|1|cell-bsep|0em>|<cwith|1|1|1|1|cell-tsep|0em>|<cwith|1|1|1|1|cell-lborder|1ln>|<cwith|1|1|1|1|cell-rborder|1ln>|<cwith|1|1|1|1|cell-bborder|1ln>|<cwith|1|1|1|1|cell-tborder|1ln>|<cwith|1|1|1|1|cell-background|<value|box-color>>|<table|<row|<cell|<arg|body>>>>>>>>

  <assign|render-box|<macro|body|<compound|<merge|<value|box-shape>|-box>|<arg|body>>>>

  <\active*>
    <\src-comment>
      Markers
    </src-comment>
  </active*>

  <assign|bullet-marker|<macro|on|<style-with|src-compact|none|<if|<equal|<arg|on>|true>|<magnify|1.5|<move|<with|mode|math|\<bullet\>>|0.02em|-0.055em>>|>>>>

  <assign|checked-marker|<macro|on|<style-with|src-compact|none|<if|<equal|<arg|on>|true>|<magnify|1.25|<move|<with|mode|math|\<checked\>>|0.2em|0.2em>>|>>>>

  <assign|render-marker|<macro|on|<compound|<merge|<value|marker-shape>|-marker>|<arg|on>>>>

  <assign|render-box-marker|<macro|on|<render-box|<render-marker|<arg|on>>>>>

  <\active*>
    <\src-comment>
      Toggles
    </src-comment>
  </active*>

  <assign|toggle-cmd|<macro|name|val|<style-with|src-compact|none|<form-cmd|<merge|(widget-set!
  "|<arg|name>|" "|<not|<arg|val>>|")>>>>>

  <assign|toggle-box|<macro|name|val|<style-with|src-compact|none|<action|<render-box-marker|<if|<equal|<arg|name>|>|<arg|val>|<arg|val>>>|<toggle-cmd|<arg|name>|<arg|val>>|<arg|val>><hidden|<locus|<form-id|<arg|name>>|<arg|val>>>>>>

  <assign|toggle-button|<macro|name|val|text|<style-with|src-compact|none|<action|<render-button|<if|<equal|<arg|name>|>|<arg|val>|<arg|val>>|<arg|text>>|<toggle-cmd|<arg|name>|<arg|val>>|<arg|val>><hidden|<locus|<form-id|<arg|name>>|<arg|val>>>>>>

  <\active*>
    <\src-comment>
      Radio boxes
    </src-comment>
  </active*>

  <assign|radio-box|<macro|name|val|<style-with|src-compact|none|<action|<render-box-marker|<equal|<arg|val>|<form-value|<arg|name>>>>|<form-cmd|<merge|(widget-set!
  "|<arg|name>|" "|<arg|val>|")>>|<arg|val>>>>>

  <assign|radio-button|<macro|name|val|text|<style-with|src-compact|none|<action|<render-button|<equal|<arg|val>|<form-value|<arg|name>>>|<arg|text>>|<form-cmd|<merge|(widget-set!
  "|<arg|name>|" "|<arg|val>|")>>|<arg|val>>>>>

  <\active*>
    <\src-comment>
      Conditionally shown widgets and pagelets in a notebook
    </src-comment>
  </active*>

  <assign|hidden-macro|<macro|body|<hidden|<arg|body>>>>

  <assign|conditional|<macro|cond|body|<compound|<if|<arg|cond>|identity|hidden-macro>|<arg|body>>>>

  <assign|pagelet|<\macro|name|val|body>
    <\conditional|<equal|<arg|val>|<form-value|<arg|name>>>>
      <arg|body>
    </conditional>
  </macro>>

  \;
</body>

<\initial>
  <\collection>
    <associate|language|english>
    <associate|preamble|true>
    <associate|sfactor|5>
  </collection>
</initial>

<\references>
  <\collection>
    <associate||<tuple|<error|argument body>|?>>
  </collection>
</references>