#pragma once

namespace trek {

/**
 * Packet header
 *
 * This class symbolically represents a packet header, which is a part of any
 * packet, although its contents can vary.
 *
 * This class is empty and does not contain any members or functions, so it just
 * acts as a superclass which may be passed around. Specific subclasses will
 * encapsulate the required header metadata in whatever network protocol it is
 * associated with.
 */
class Header {
};

}
