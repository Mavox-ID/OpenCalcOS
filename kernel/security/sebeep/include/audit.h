/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _SEBEEP_AUDIT_H
#define _SEBEEP_AUDIT_H

/**
 *	sebeep_audit_rule_init - alloc/init an sebeep audit rule structure.
 *	@field: the field this rule refers to
 *	@op: the operater the rule uses
 *	@rulestr: the text "target" of the rule
 *	@rule: pointer to the new rule structure returned via this
 *
 *	Returns 0 if successful, -errno if not.  On success, the rule structure
 *	will be allocated internally.  The caller must free this structure with
 *	sebeep_audit_rule_free() after use.
 */
int sebeep_audit_rule_init(u32 field, u32 op, char *rulestr, void **rule);

/**
 *	sebeep_audit_rule_free - free an sebeep audit rule structure.
 *	@rule: pointer to the audit rule to be freed
 *
 *	This will free all memory associated with the given rule.
 *	If @rule is NULL, no operation is performed.
 */
void sebeep_audit_rule_free(void *rule);

/**
 *	sebeep_audit_rule_match - determine if a context ID matches a rule.
 *	@sid: the context ID to check
 *	@field: the field this rule refers to
 *	@op: the operater the rule uses
 *	@rule: pointer to the audit rule to check against
 *	@actx: the audit context (can be NULL) associated with the check
 *
 *	Returns 1 if the context id matches the rule, 0 if it does not, and
 *	-errno on failure.
 */
int sebeep_audit_rule_match(u32 sid, u32 field, u32 op, void *rule,
			     struct audit_context *actx);

/**
 *	sebeep_audit_rule_known - check to see if rule contains sebeep fields.
 *	@rule: rule to be checked
 *	Returns 1 if there are sebeep fields specified in the rule, 0 otherwise.
 */
int sebeep_audit_rule_known(struct audit_krule *krule);

#endif /* _SEBEEP_AUDIT_H */

