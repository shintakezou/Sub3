#include "DummyVessel.hpp"

//IMPORTANT: This lets Boost serialize our spawn message.
REGISTER_PACKETS(DummyVessel, "DummyVessel")

DummyVessel::DummyVessel()
{
}

VesselState DummyVessel::getNewState(float dt)
{
    return mState;
}

std::vector<std::shared_ptr<Message> > DummyVessel::getSpawnMessages(VesselID vesselID)
{
    //Just return the one spawn message. Nothing special here.
    std::vector<std::shared_ptr<Message> > messages;
    messages.push_back(std::make_shared<SpawnMessage<DummyVessel> >(vesselID, mState));
    return messages;
}

std::shared_ptr<Vessel::VesselUI> DummyVessel::constructUI()
{
    return std::make_shared<DummyVessel::DummyUI>();
}

DummyVessel::DummyUI::~DummyUI()
{
}

std::shared_ptr<sfg::Widget> DummyVessel::DummyUI::setupUI()
{
    return sfg::Label::Create("Hello");
}

void DummyVessel::DummyUI::updateUI(double dt)
{
}
