#include "Ocean.hpp"
#include "Vessel.hpp"

#include <boost/assert.hpp>

Ocean* Ocean::oceanInst = NULL;

Ocean::Ocean() :
    mMonth(Month::Undefined)
{
}

Ocean* Ocean::getOcean()
{
    if (!oceanInst)
    {
        oceanInst = new Ocean();
    }
    return oceanInst;
}

std::vector<std::shared_ptr<Message> > Ocean::tick(float dt) const
{
    //TODO: update the world.
}

std::vector<std::shared_ptr<Message> > Ocean::getInitiationMessages() const
{
    //Loop through all the vessels and ask them for the messages required to duplicate them.
    std::vector<std::shared_ptr<Message> > messages;
    for (auto const & kv : mVessels)
    {
        //Get spawn messages.
        auto newMessages = kv.second->getSpawnMessages(kv.first);
        //Add them to the master list.
        messages.insert(messages.end(), newMessages.begin(), newMessages.end());
    }
    return messages;
}

void Ocean::localResetOcean()
{
    mVessels.clear();
}

void Ocean::localSpawnVessel(VesselID id, std::shared_ptr<Vessel> vessel)
{
    subDebug << "Ocean: Spawning " << id << std::endl;
    BOOST_ASSERT_MSG(!mVessels.count(id), "Fatal: Ocean already contains vessel to be spawned");
    mVessels[id] = vessel;
}

void Ocean::localDespawnVessel(VesselID id)
{
    subDebug << "Ocean: Despawning " << id << std::endl;
    BOOST_ASSERT_MSG(mVessels.count(id), "Fatal: Ocean doesn't contain vessel to be despawned");
    mVessels.erase(id);
}

void Ocean::localUpdateVessel(VesselID id, VesselState state)
{
    subDebug << "Ocean: Updating " << id << std::endl;
    BOOST_ASSERT_MSG(mVessels.count(id), "Fatal: Ocean doesn't contain vessel to be updated");
    mVessels[id]->setState(state);
}

void Ocean::localSetMonth(Ocean::Month month)
{
    mMonth = month;
}

Ocean::Month Ocean::getMonth()
{
    return mMonth;
}

bool Ocean::getHasVessel(VesselID id)
{
    return mVessels.count(id) != 0;
}

VesselState Ocean::getState(VesselID id)
{
    BOOST_ASSERT_MSG(getHasVessel(id), "Fatal: Ocean doesn't contain vessel to get state of");
    return mVessels.at(id)->getState();
}
