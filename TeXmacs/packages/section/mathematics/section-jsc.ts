<TeXmacs|1.0.4>

<style|source>

<\body>
  <active*|<\src-title>
    <src-package|section-jsc|1.0>

    <\src-purpose>
      Sectional markup for the jsc style.
    </src-purpose>

    <src-copyright|1998--2004|Joris van der Hoeven>

    <\src-license>
      This <TeXmacs> style package falls under the <hlink|GNU general public
      license|$TEXMACS_PATH/LICENSE> and comes WITHOUT ANY WARRANTY
      WHATSOEVER. If you do not have a copy of the license, then write to the
      Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
      02111-1307, USA.
    </src-license>
  </src-title>>

  <use-package|section-article>

  \;

  <assign|sectional-sep|<macro|.<space|2spc>>>

  <assign|sectional-normal|<macro|name|<no-indent><arg|name><no-page-break>>>

  <\active*>
    <\src-comment>
      Sections, subsections and subsubsections.
    </src-comment>
  </active*>

  <assign|section-title|<macro|name|<style-with|src-compact|none|<sectional-centered-bold|<vspace*|1fn><arg|name><vspace|1fn>>>>>

  <assign|subsection-title|<macro|name|<style-with|src-compact|none|<sectional-centered|<vspace*|1fn><with|font-shape|small-caps|<arg|name>><vspace|1fn>>>>>

  <assign|subsubsection-title|<macro|name|<style-with|src-compact|none|<sectional-normal|<vspace*|1fn><with|font-shape|small-caps|<arg|name>><vspace|1fn>>>>>

  <\active*>
    <\src-comment>
      Paragraphs and subparagraphs.
    </src-comment>
  </active*>

  <assign|paragraph-title|<macro|name|<style-with|src-compact|none|<sectional-short|<vspace*|0.5fn><with|font-shape|small-caps|<arg|name><paragraph-sep>>>>>>

  <assign|subparagraph-title|<macro|name|<style-with|src-compact|none|<sectional-short|<vspace*|0.5fn><with|font-shape|small-caps|<arg|name><subparagraph-sep>>>>>>

  \;
</body>

<\initial>
  <\collection>
    <associate|preamble|true>
  </collection>
</initial>