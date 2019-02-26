/* Inventory and item test */
// vim: set ft=c tw=72 fdm=marker:

/* System includes */
#include <stdio.h>

/* Local includes */
#include <inventory.h>
#include <item.h>
#include <wset.h>


// PRINTING FUNCTIONS {{{
/* Print flag */
void print_flag(flag_t *flag)
{
    if (flag->yes && flag->no) {
        if (flag->state) {
            printf("%s", flag->yes);
        } else {
            printf("%s", flag->no);
        }
    }
}

/* Print qualities */
void print_qltys(qltys_t *qltys)
{
    if (qltys && qltys->len != 0) {
        printf("  > ");
        for (size_t i = 0; i < qltys->len; ++i) {
            print_flag(qltys->flags[i]);
            if (i < qltys->len - 1) {
                printf(", ");
            }
        }
        puts("");
    }
}

/* Print word set information */
void print_wset(wset_t *wset)
{
    if (wset && wset->len != 0) {
        printf("  > ");
        for (size_t i = 0; i < wset->len; ++i) {
            printf("%s", wset->words[i]);
            if (i < wset->len - 1) {
                printf(", ");
            }
        }
        puts("");
    }
}

/* Print item information */
void print_item(item_t *item)
{
    printf("%d: %s:\n", item->id, item->lingo->kname);
    print_wset(item->lingo->nouns);
    print_wset(item->lingo->adjs);
    print_wset(item->lingo->pronouns);
    print_qltys(item->qltys);
    if (item->lingo->desc) {
        printf("  %s (%g kg)\n", item->lingo->desc, item->weight);
    }
}

/* Print inventory contents */
void print_inv(inv_t *inv)
{
    printf("\nWeight: %.1f kg;  Length: %ld\n", inv_weight(inv), inv->len);
    for (size_t i = 0; i < inv->len; ++i) {
        print_item(inv->items[i]);
    }
    puts("------------------------------------");
}
// }}}


/* Main entry */
int main(void)
{
    inv_t *inv1, *inv2;
    item_t *it1, *it2, *it3, *it4;
    flag_t *fill, *heat;

    /* Initialize empty inventories */
    inv1 = inv_init();
    inv2 = inv_init();

    if (!inv1 || !inv2) {
        return 1;
    }

    /* Initialize flag */
    fill = flag_init(true, "full", "empty");
    heat = flag_init(true, "cold", "hot");

    /* Initialize items */
    it1 = item_init("mug", "It's a very nice mug", 0.2);
    it2 = item_init("pencil", "A very long pencil", 0.1);
    it3 = item_init("rock", "A very heavy rock", 4.5);
    it4 = item_init("rock", "Another heavy rock", 5.5);

    if (!it1 || !it2 || !it3 || !it4) {
        return 1;
    }

    /* Set items */
    item_add_noun(it1, "cup");
    item_add_noun(it1, "glass");
    item_add_adj(it1, "red");
    item_add_adj(it1, "");
    item_replace_adj(it1, "red", "blue");

    item_add_qlty(it1, fill);
    item_add_qlty(it1, heat);
    item_toggle_flag(it1, heat);

    /* Associate flag with adjective */
/*
    if (flag_state(heat)) {
        item_replace_adj(it1, "hot", "cold");
    } else {
        item_replace_adj(it1, "cold", "hot");
    }
*/

    /* TODO:
     *
     * Should the 'yes' and 'no' strings be passed as adjectives,
     * and then, remove the adjectives array since those came from
     * the flags?
     *
     * Maybe, leave the adjectives set only for unchanged properties,
     * such as color, shape, &c., and use flags as dynamic adjectives.
     */


    /* Add and remove items to inventories */
    inv_add(inv1, it1);
    inv_add(inv1, it2);
    inv_add(inv1, it3);
    inv_add(inv1, it4);
    inv_add(inv1, it4);
    inv_rem(inv1, it4);
    inv_add(inv2, it4);
    inv_rem(inv1, it3);
    inv_add(inv2, it3);

    /* Transfer items between inventories */
    inv_transfer(inv2, inv1, it4);
    inv_transfer(inv1, inv2, it3);

    /* Print inventories */
    print_inv(inv1);
    print_inv(inv2);

    /* Destroy inventories (the items are not destroyed) */
    inv_destroy_hard(inv1);
    inv_destroy_hard(inv2);

    return 0;
}

