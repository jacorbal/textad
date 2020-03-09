Text Adventure
==============

Text adventure is a interactive fiction minimal engine in C, still in development.


Intention
---------

    All sentences are imperative in the form:

       <action> [<mode>] [<quality>] [<quantity>] [<dir.obj>] [<ind.obj>]
       -------- -------- ----------- ------------ ----------- -----------
          |        |         |            |            |              |
        VERB    ADVERB    ADJECTIVE    NUMBER     COMMON NOUN  PRONOUN or
          |                                                    PROPER NOUN
          |
       Mandatory

    Examples:
      * INVENTORY (verb -> special)
      * GET KEY (verb + noun)
      * GIVE KEY TO HIM (verb + noun + "to" + iobj)
      * ASK HER ABOUT MAGIC (verb + pronoun + "about" + dobj)
      * LOOK IN RED CLOSET (verb + "in" + adj + dobj)
      * TAKE SWORD AND KILL MONSTER FEROCEOSLY
             (verb + dobj) + "AND" + (verb + dobj + adv)
      * ASK HIM SOFTLY ABOUT THE THREE RED BIRDS
             (verb + iobj + adv + "about" + "the" + num + adj + noun)

    The <action> (verb) is always required.  It can be a tipical action,
    but also an special command (such as "inventory"), an answer ("yes",
    "no", "maybe"), a direction ("north", "east"), &c.

    When a special action is invoked, everything else is ignored:
      * LOAD QUICKLY (load + <ignored>)
      * SAVE GENTLY (save + <ignored>)
      * INVENTORY NOW (inventory + <ignored>)

    Prepositions, articles and conjunctions are ignored, except 'and' to
    couple several actions into one, eg, "LOOK ROOM AND TAKE KEY".


License
-------

This software is available under [MIT license](LICENSE).  For more
information you may read <https://opensource.org/licenses/MIT>.

In short words:

  * You **may**:

    - Use the work commercially
    - Make changes to the work
    - Distribute the compiled code and/or source
    - Incorporate the work into something with a more restrictive license
    - Use the work for private use

  * You **cannot**:

    - Hold the author liable (the work is provided "as is")

  * You **must include**:

    - The copyright notice in all copies or substantial uses of the work
    - The license notice in all copies or substantial uses of the work


Copyright
---------

Copyright (c) 2019-2020, J. A. Corbal
