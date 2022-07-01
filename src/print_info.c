#include <stdio.h>
#include "creature.h"
#include "item.h"
#include "data.h"
#include "effects.h"
#include "level.h"


void print_creature(Creature* creature)
{
	printf("id: %d\n", creature->id);
	printf("position: (%d; %d)\n", creature->pos_x, creature->pos_y);
	printf("name: %s\n", creature->name);
	printf("type: %d\n", creature->type);
	printf("max stats: str %d, dex %d, con %d, int %d, wis %d, chr %d\n", creature->max_strength, creature->max_dexterity, creature->max_constitution, creature->max_intelligence, creature->max_wisdom, creature->max_charisma);
	printf("cur stats: str %d, dex %d, con %d, int %d, wis %d, chr %d\n", creature->cur_strength, creature->cur_dexterity, creature->cur_constitution, creature->cur_intelligence, creature->cur_wisdom, creature->cur_charisma);
	printf("max ap: %d\n", creature->max_ap);
	printf("cur ap: %d\n", creature->cur_ap);

	printf("effects:\n");
	for (int i = 0; i < CREATURE_MAX_EFFECTS; ++i)
		printf("type: %d, time left: %d\n", creature->effects[i].type, creature->effects[i].time_left);

	printf("body:\n");
	for (int i = 0; i < MAX_LIMBS; ++i)
	{
		printf("type: %d\n", creature->body[i].type);
		printf("cur hp: %d, max hp: %d\n", creature->body[i].hp, creature->body[i].max_hp);
		printf("armor id: %d, weapon id: %d\n", creature->body[i].armor_id, creature->body[i].weapon_id);
	}

	printf("general hp: %d, max: %d\n", creature->hp, creature->max_hp);
	printf("cur satiety: %d, max satiety: %d\n", creature->cur_satiety, creature->max_satiety);
	printf("metabolism: %d\n", creature->metabolism);
	printf("lifted weight: %f\n", creature->lifted_weight);
	printf("lift limit: %f\n", creature->lift_limit);

	printf("inventory:\n%d;", creature->inventory[0]);
	for (int i = 1; i < CREATURE_MAX_ITEMS; ++i)
		printf(" %d;", creature->inventory[i]);
	printf("%d items\n", creature->cur_items);

	printf("cur enemies:\n%d;", creature->cur_enemies[0]);
	for (int i = 1; i < CREATURE_MAX_ENEMIES; ++i)
		printf(" %d;", creature->cur_enemies[i]);
	printf("\n");

	printf("cur friends:\n%d;", creature->cur_friends[0]);
	for (int i = 1; i < CREATURE_MAX_FRIENDS; ++i)
		printf(" %d;", creature->cur_friends[i]);
	printf("\n");

	printf("sight distance: %d\n", creature->sight_distance);

	if (creature->flags & CREATURE_IS_HIDDEN) printf("! creature is hidden\n");
}




void print_item(Item* item)
{
	printf("id: %d\n", item->id);
	printf("name: %s\n", item->name);
	printf("type: %d\n", item->type);
	printf("position: (%d; %d)\n", item->pos_x, item->pos_y);
	printf("weight: %f\n", item->weight);
	printf("number: %d\n", item->number);

	printf("effects:\n");
	for (int i = 0; i < ITEM_MAX_EFFECTS; ++i)
		printf("type: %d, time left: %d\n", item->effects[i].type, item->effects[i].time_left);

	printf("category: %d\n", item->category);

	switch (item->category)
	{
		case ITEM_WEAPON:
			printf("melee damage: %d, ranged damage: %d\n", item->info.weapon.melee_damage, item->info.weapon.ranged_damage);
			printf("ranged break number: %d\n", item->info.weapon.ranged_break_number);
			printf("effect type when melee struck: %d\n", item->info.weapon.effect.type);
			printf("effect time left: %d\n", item->info.weapon.effect.time_left);
			printf("cur condition: %d, max condition: %d\n", item->info.weapon.cur_condition, item->info.weapon.max_condition);
			break;

		case ITEM_ARMOR:
			printf("armor defence: %d\n", item->info.armor.defence);
			printf("armor limb type: %d\n", item->info.armor.limb_type);
			printf("worn effect type: %d\n", item->info.armor.effect_type);
			printf("cur condition: %d, max condition: %d\n", item->info.armor.cur_condition, item->info.armor.max_condition);
			break;

		case ITEM_MISSILE:
			printf("missile weapon type: %d\n", item->info.missile.weapon_type);
			printf("missile damage: %d\n", item->info.missile.damage);
			printf("effect type: %d, time left: %d\n", item->info.missile.effect.type, item->info.missile.effect.time_left);
			break;

		case ITEM_COMESTIBLE:
			printf("nutrition: %d\n", item->info.comestible.nutrition);
			printf("left shelf life: %d, max shelf life: %d\n", item->info.comestible.shelf_life_left, item->info.comestible.shelf_life_max);
			printf("comested effect type: %d, time left: %d\n", item->info.comestible.comested_effect.type, item->info.comestible.comested_effect.time_left);
			printf("rotten effect type: %d, time left: %d\n", item->info.comestible.rotten_effect.type, item->info.comestible.rotten_effect.time_left);
			break;

		case ITEM_NOTE:
			printf("note text: %s\n", item->info.note.text);
			printf("note type: %d\n", item->info.note.type);
			printf("reveal coords:\n");
			for (int i = 0; i < NOTE_REVEAL_MAX; ++i)
				printf("(%d, %d)\n", item->info.note.reveal_x[i], item->info.note.reveal_y[i]);
			printf("numofreveal: %d\n", item->info.note.numofreveal);
			break;
	}

	if (item->flags & ITEM_IS_UNSTACKABLE) printf("! item is unstackable\n");
	if (item->flags & ITEM_IS_HIDDEN) printf("! item is hidden\n");
	if (item->flags & ITEM_IS_IN_INVENTORY) printf("! item is in inventory\n");
	if (item->flags & WEAPON_IS_TWO_HANDED) printf("! weapon is two handed\n");
	if (item->flags & RANGED_NEEDS_STRENGTH) printf("! ranged weapon needs strength\n");
}




void print_tile(struct Level* level, int x, int y)
{
	Tile* tile = GET_TILE(level, x, y);
	printf("on (%d; %d):\n", x, y);
	printf("creature id: %d\n", tile->creature_id);
	printf("item ids: %d", tile->item_ids[0]);
	for (int i = 1; i < tile->items_number; ++i)
		printf(", %d", tile->item_ids[i]);
	printf("\n");
	printf("feature id: %d\n", tile->feature_id);
	if (tile->flags & TILE_IS_PASSABLE) printf("! tile is passable\n");
	if (tile->flags & TILE_IS_TRANSPARENT) printf("! tile is transparent\n");
	if (tile->flags & TILE_IS_DESTROYABLE) printf("! tile is destroyable\n");
	if (tile->flags & TILE_CAN_BURN) printf("! tile can burn\n");
	if (tile->flags & TILE_IS_BURNING) printf("! tile is burning\n");
	if (tile->flags & TILE_IS_WORKSHOP) printf("! tile is workshop\n");
	if (tile->flags & TILE_IS_FORGE) printf("! tile is forge\n");
	if (tile->flags & TILE_IS_KITCHEN) printf("! tile is kitchen\n");
	if (tile->flags & TILE_IS_ALCHEMERY) printf("! tile is alchemery\n");
	if (tile->flags & TILE_IS_ENDING_POINT) printf("! tile is ending point\n");
}
