/*
   $Id: log_entry.h,v 1.2 2004/07/25 12:14:41 ksterker Exp $
   
   Copyright (C) 2004 Kai Sterker <kaisterker@linuxgames.com>
   Part of the Adonthell Project http://adonthell.linuxgames.com

   Adonthell is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Adonthell; if not, write to the Free Software 
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


/**
 * @file   rpg/log_entry.h
 * @author Kai Sterker <kaisterker@linuxgames.com> 
 * 
 * @brief  Log book entry.
 */

#ifndef RPG_LOGENTRY_H
#define RPG_LOGENTRY_H

#include "base/types.h"
#include <string>

namespace rpg
{
    /**
     * The %log_entry class encapsulates a single entry into one of the log books. Each entry
     * consists of a topic, the main text and a time stamp. It will also have a unique id to
     * allow cross-references and an index.
     */
    class log_entry
    {
        public:
            /**
             * Creates a new log entry.
             * @param topic 'Headline' of the entry.
             * @param text content of entry.
             * @param uid unique identifier for entry. Used by log index.
             */
            log_entry (const std::string & topic, const std::string & text, const std::string & uid);
            
            /**
             *
             */
            std::string text () const { return Text; }
            
            /**
             *
             */
            std::string uid () const { return Uid; }
            
            // void get_state (base::flat in);
            
            // bool put_state (base::flat out);
            
        private:
            /// creation time of log entry
            u_int32 Timestamp;
            /// main text of entry 
            std::string Text;
            /// topic of entry
            std::string Topic;
            /// unique id
            std::string Uid;
    };
}

#endif // RPG_LOGENTRY_H