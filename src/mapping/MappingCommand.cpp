//---------------------------------------------------------------------------------------------------------------------
//   MIT License
//
//   Copyright (c) 2021 Marco Auer
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
//   documentation files (the "Software"), to deal in the Software without restriction, including without limitation
//   the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
//   to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in all copies or substantial portions of
//   the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//   THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
//   CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//   IN THE SOFTWARE.
//---------------------------------------------------------------------------------------------------------------------

// XMidiCtrl
#include "Logger.h"
#include "MappingCommand.h"

namespace XMidiCtrl {

//---------------------------------------------------------------------------------------------------------------------
//   CONSTRUCTOR / DESTRUCTOR
//---------------------------------------------------------------------------------------------------------------------

/**
 * Constructor
 */
MappingCommand::MappingCommand(XPlane::ptr xplane, int controlChange)
        : Mapping(std::move(xplane), controlChange) {}




//---------------------------------------------------------------------------------------------------------------------
//   PUBLIC
//---------------------------------------------------------------------------------------------------------------------

/**
 * Return the mapping type
 */
MappingType MappingCommand::type() {
    return MappingType::Command;
};


/**
 * Set the command
 */
void MappingCommand::setCommand(std::string_view command) {
    m_command = command;
}


/**
 * Return the command
 */
std::string_view MappingCommand::command() const {
    return m_command;
}


/**
 * Check the mapping
 */
bool MappingCommand::check() {
    if (!Mapping::check())
        return false;

    if (m_command.empty())
        return false;
    else
        return true;
}


/**
 * Execute the action in X-Plane
 */
void MappingCommand::execute(MidiEvent::ptr midiEvent) {
    switch (midiEvent->velocity) {
        case 127:
            m_xplane->commands()->begin(m_command);
            break;

        case 0:
            m_xplane->commands()->end(m_command);
            break;

        default:
            LOG_ERROR << "Invalid Midi status '" << midiEvent->status << "'" << LOG_END
    }
}

} // Namespace XMidiCtrl