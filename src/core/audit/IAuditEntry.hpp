/*
    Copyright (C) 2014-2016 Islog

    This file is part of Leosac.

    Leosac is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Leosac is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "core/audit/AuditFwd.hpp"
#include "core/auth/AuthFwd.hpp"
#include <memory>

namespace Leosac
{
namespace Audit
{
/**
 * Base interface to Audit object.
 *
 * This interface is inherited by all "behavior specific" audit object, such as
 * IWSAPICall (when a websocket API call is made) or IUserEvent when something
 * happens to a user.
 *
 * There are 2 main reasons for using an interface here:
 *     + It reduces the required include for files that will use Audit object.
 *       Indeed, only the interface file and the AuditFactory header are required.
 *       No need to include various ODB headers.
 *     + Allows us the use of factory function to create Audit object. This provides
 *       stronger garantee against bugs, as part of the object lifecycle is
 *       managed the factory function.
 */
class IAuditEntry
{
  public:
    /**
     * Retrieve the identifier of the entry.
     *
     * An `id` of 0 means that the entry is not persisted yet.
     */
    virtual AuditEntryId id() const = 0;

    /**
     * Mark the entry as finalized, and update it wrt the database.
     *
     * Calling `finalize()` on an already finalized entry has no effect.
     *
     * Subclasses must prevent modification of every attributes
     * once this method has been called.
     *
     * Pre-Conditions:
     *     + Must be in a database transaction.
     *
     * @warning While updating the object state in the database, the transaction
     * itself is not `commit()`ed. Make sure to commit the transaction to garantee
     * that the audit is stored in the database.
     */
    virtual void finalize() = 0;

    /**
     * Is this entry finalized.
     */
    virtual bool finalized() const = 0;

    /**
     * Set the event mask for the entry.
     * @param mask
     */
    virtual void event_mask(const EventMask &mask) = 0;

    /**
     * Retrieve the current event mask.
     */
    virtual const EventMask &event_mask() const = 0;

    /**
     * Set the author of the entry.
     *
     * The author is the user that is responsible (aka at the source)
     * of the event.
     *
     * Pre-Conditions:
     *     + The `user` pointer, if not null, must point to an already persisted
     *     user object.
     */
    virtual void author(Auth::UserPtr user) = 0;

    /**
     * Set `parent` as the parent audit entry for
     * this entry.
     *
     * The `set_parent()` will copy the parent's author to this->author_
     * if there currently is no author assigned to the entry.
     *
     * Pre-Conditions:
     *     + Shall be already persisted (otherwise we might give the parent
     *       a non persisted child, resulting in foreign key issue).
     *     + Shall have no parent.
     *     + The `parent` must be a non-null, already persisted
     *       object.
     *     + `parent` must be of type AuditEntryPtr. This should always
     *       be the case.
     *
     * Post-Conditions:
     *     + Will have a parent.
     *     + This object will be somewhere in `parent->children_` array.
     */
    virtual void set_parent(IAuditEntryPtr parent) = 0;
};
}
}
