#ifndef HARVESTEROBJECTMESSAGE7_H_
#define HARVESTEROBJECTMESSAGE7_H_

#include "../BaseLineMessage.h"

#include "../../objects/installation/harvester/HarvesterObject.h"
#include "server/zone/objects/resource/ResourceSpawn.h"

class HarvesterObjectMessage7 : public BaseLineMessage {
public:
	HarvesterObjectMessage7(HarvesterObject* hino)
			: BaseLineMessage(hino->getObjectID(), 0x48494E4F, 7, 0x05) {

		insertByte(1);

		Vector<ManagedReference<ResourceSpawn*> > resourceList;
		ResourceManager* resourceManager = hino->getZoneServer()->getResourceManager();

		insertResourceIDList(&resourceList);
		insertResourceNameList(&resourceList);
		insertResourceTypeList(&resourceList);

		/*insertLong(hino->getActiveResourceID());
		insertByte(hino->isOperating());
		insertFloat(hino->getActualRate());
		insertFloat(hino->getSpecRate());
		insertFloat(hino->getTotalHopperQuantity());
		insertFloat(hino->getCapacity());

		insertInt(hino->getHopperSize());*/

		insertLong(hino->getActiveResourceID());
		insertByte(hino->isOperating());
		insertInt((int)hino->getExtractionRate()); // Extraction Rate Displayed
		insertFloat(hino->getExtractionRate()); // Extract Rate Max

		insertFloat(hino->getActualRate()); // Current Extract Rate

		insertFloat(hino->getHopperSize());
		insertInt((int)hino->getHopperSizeMax());

		insertHopperItems(hino);
		insertByte(100); // Percentage of Condition

		setSize();

	}

	void insertResourceIDList(Vector<ManagedReference<ResourceSpawn*> >* hino) {
		for (int x = 0; x < 2; x++) {
			insertInt(hino->size());
			insertInt(hino->size());
			for (int i = 0; i < hino->size(); i++) {
				insertLong(hino->get(i)->getObjectID());
			}
		}
	}

	void insertResourceNameList(Vector<ManagedReference<ResourceSpawn*> >* hino) {
		insertInt(hino->size());
		insertInt(hino->size());
		for (int i = 0; i < hino->size(); i++) {
			insertAscii(hino->get(i)->getName());
		}
	}

	void insertResourceTypeList(Vector<ManagedReference<ResourceSpawn*> >* hino) {
		insertInt(hino->size());
		insertInt(hino->size());
		for (int i = 0; i < hino->size(); i++) {
			insertAscii(hino->get(i)->getType());
		}
	}

	void insertHopperItems(HarvesterObject * hino) {
		HopperList* hopperList = hino->getHopperList();

		if (hopperList->size() == 0)
			insertByte(0);
		else
			insertByte(hopperList->size() + 1);

		hopperList->insertToMessage(this);
	}
};
#endif /*HARVESTEROBJECTMESSAGE7_H_*/
