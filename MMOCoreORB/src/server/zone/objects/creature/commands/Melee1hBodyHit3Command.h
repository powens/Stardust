/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MELEE1HBODYHIT3COMMAND_H_
#define MELEE1HBODYHIT3COMMAND_H_

#include "CombatQueueCommand.h"

class Melee1hBodyHit3Command : public CombatQueueCommand {

protected:
	String skillName = "melee1hbodyhit3";		// Skill Name
	String skillNameDisplay = "Advanced One-Hand Body Hit";		// Skill Display Name for output message
	int delay = 36; 								//  30 second cool down timer after root expires

public:

	Melee1hBodyHit3Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

						if (!checkStateMask(creature))
							return INVALIDSTATE;

						if (!checkInvalidLocomotions(creature))
							return INVALIDLOCOMOTION;
						ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
						CreatureObject* targetCreature = dynamic_cast<CreatureObject*>(object.get());

						if (targetCreature == NULL)
							return INVALIDTARGET;

						Locker clocker(targetCreature, creature);

						ManagedReference<PlayerObject*> player = creature->getPlayerObject();
						PlayerObject* targetPlayerObject = targetCreature->getPlayerObject();

						if (targetPlayerObject == NULL) {
							return INVALIDTARGET;
						} else if (player == NULL)
							return GENERALERROR;



						int res = doCombatAction(creature, target);

						if (res == SUCCESS) {

							// Setup debuff.

							if (!creature->checkCooldownRecovery(skillName)){
											Time* timeRemaining = creature->getCooldownTime(skillName);
											creature->playMusicMessage("sound/ui_negative.snd");
											creature->sendSystemMessage("Your target can not be rooted with " + skillNameDisplay + " for another " +  getCooldownString(timeRemaining->miliDifference() * -1));
							}

							else if (targetCreature != NULL) {
								Locker clocker(targetCreature, creature);

								ManagedReference<Buff*> buff = new Buff(targetCreature, getNameCRC(), 6, BuffType::OTHER);

								Locker locker(buff);
								if (targetCreature->hasBuff(STRING_HASHCODE("burstrun")) || targetCreature->hasBuff(STRING_HASHCODE("retreat")) || targetCreature->hasBuff(BuffCRC::JEDI_FORCE_RUN_1)) {
									targetCreature->removeBuff(STRING_HASHCODE("burstrun"));
									targetCreature->removeBuff(STRING_HASHCODE("retreat"));
									targetCreature->removeBuff(BuffCRC::JEDI_FORCE_RUN_1);
								}

								buff->setSpeedMultiplierMod(0.01f);
								buff->setAccelerationMultiplierMod(0.01f);
								targetCreature->setSnaredState(10);
								targetCreature->playEffect("clienteffect/commando_position_secured.cef", "");
								StringBuffer targetRootMessage;

								targetRootMessage << "You have been rooted!";
								targetCreature->sendSystemMessage(targetRootMessage.toString());

								targetCreature->addBuff(buff);
								creature->sendSystemMessage("You successfully root your target!");
								creature->updateCooldownTimer(skillName, delay * 1000);

							}

						}
						return res;
					}

					String getCooldownString(uint32 delta) const {

						int seconds = delta / 1000;

						int hours = seconds / 3600;
						seconds -= hours * 3600;

						int minutes = seconds / 60;
						seconds -= minutes * 60;

						StringBuffer buffer;

						if (hours > 0)
							buffer << hours << "h ";

						if (minutes > 0)
							buffer << minutes << "m ";

						if (seconds > 0)
							buffer << seconds << "s";

						return buffer.toString();
					}

			};

#endif //MELEE1HBODYHIT3COMMAND_H_
