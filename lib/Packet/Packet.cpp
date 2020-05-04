#include "Packet.h"

using namespace trek;

Packet::Packet(int id, uint32_t size, const Label& label) :
    id(id), size(size), label(new Label(label.src, label.dest)) {}

uint32_t Packet::getSize() const { return size; }
const Label& Packet::getLabel() const { return *label; }

void Packet::setLabel(const Label& n_label)
{
    label->src = n_label.src;
    label->dest = n_label.dest;
}
