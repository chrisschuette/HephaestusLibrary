/* 
 * File:   Button.h
 * Author: chris
 *
 * Created on February 2, 2014, 7:05 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "../Component.h"
#include <boost/signals2.hpp>

namespace GUI {
    namespace COMPONENTS {

        class Button : public Component {
            typedef boost::signals2::signal<void () > click_signal_type;
            typedef click_signal_type::slot_type click_slot_type;
        public:
            Button();
            Button(const std::string buttonText);
            Button(const std::string* buttonText);
            virtual ~Button();
            virtual void handleEvent(const EVENT::Event& event);
            bool click(const click_slot_type& s);
            std::string getButtonText() const { return m_buttonText; }
        private:
            click_signal_type m_clickedSignal;
            std::string m_buttonText;
            
        };
    }
}
#endif	/* BUTTON_H */

