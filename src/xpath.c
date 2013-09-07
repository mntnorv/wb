/*
 * Copyright (C) 2013 Mantas Norvaiša
 *
 * This file is part of wb.
 * 
 * wb is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * wb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with wb.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include "xpath.h"

/**
 * Initializes the XPath system
 */
void xpath_init() {
	xmlInitParser();
}

/**
 * Cleans up the XPath system
 */
void xpath_cleanup() {
	xmlCleanupParser();
}

/**
 * Registers the specified namespaces with an XML XPath context.
 *
 * @param xpath_context - a pointer to a xmlXPathContext structure
 * @param namespaces - a list of namespaces, containing two elements
 *   for every namespace: a prefix, and a href (in that order).
 * @return 0 on success, -1 otherwise
 */
int
libxml_xpath_register_namespaces(xmlXPathContextPtr xpath_context,
	struct wb_str_list *namespaces) {

	struct wb_str_list *current_ns = namespaces;
	char *prefix, *href;
	int res;

	while (current_ns != NULL) {
		prefix = current_ns->str;
		current_ns = current_ns->next;

		if (current_ns != NULL) {
			href = current_ns->str;
			current_ns = current_ns->next;
		} else {
			return -1;
		}

		res = xmlXPathRegisterNs(xpath_context,
			BAD_CAST prefix, BAD_CAST href);

		if (res != 0) {
			return -1;
		}
	}

	return 0;
}

/**
 * Evaluates an XPath expression on the given XML file.
 *
 * @param xml_doc - the XML document pointer.
 * @param expression - the expressions to evaluate.
 * @param namespaces - a list of namespaces, containing two elements
 *   for every namespace: a prefix, and a href (in that order).
 * @return an xmlXPathObjectPtr with the results on success, NULL
 *   otherwise. IMPORTANT: the returned object must be freed with
 *   xmlXPathFreeObject().
 */
xmlXPathObjectPtr
libxml_xpath_eval_expr(xmlDocPtr xml_doc, const xmlChar *expression, 
	struct wb_str_list *namespaces) {

	xmlXPathContextPtr xpath_context;
	xmlXPathObjectPtr xpath_object;

	/* Create XPath context */
	xpath_context = xmlXPathNewContext(xml_doc);
	if (xpath_context == NULL) {
		return NULL;
	}

	/* Add XML namespace for XHTML */
	if (libxml_xpath_register_namespaces(xpath_context, namespaces) != 0) {
		xmlXPathFreeContext(xpath_context);
		return NULL;
	}

	/* Evaluate XPath expression */
	xpath_object = xmlXPathEvalExpression(expression, xpath_context);
	if (xpath_object == NULL) {
		xmlXPathFreeContext(xpath_context);
		return NULL;
	}

	/* Clean up */
	xmlXPathFreeContext(xpath_context);

	return xpath_object;
}

/**
 * Converts a XML XPath object to a list of strings. Assumes
 * that every node in the object is a text node.
 *
 * @param xpath_object - the object to be converted
 * @param xml_doc - the parent XML document
 * @return a wb_str_list containing the converted object on success,
 *   NULL otherwise. IMPORTANT: the returned list must be frees with
 *   wb_list_free().
 */
struct wb_str_list *
xpath_object_to_str_list(xmlXPathObjectPtr xpath_object, xmlDocPtr xml_doc) {
	struct wb_str_list *obj_list = NULL;

	xmlNodeSetPtr object_nodes;
	xmlNodePtr current_node;
	xmlChar *current_str;
	int i, object_node_count;

	object_nodes = xpath_object->nodesetval;
	object_node_count = (object_nodes) ? object_nodes->nodeNr : 0;

	for (i = 0; i < object_node_count; i++) {
		current_node = object_nodes->nodeTab[i];
		current_str = xmlNodeListGetString(xml_doc, current_node->xmlChildrenNode, 1);
		if (current_str != NULL) {
			obj_list = wb_list_append(obj_list, (char *)current_str);
			xmlFree(current_str);
		}
	}

	return obj_list;
}

/**
 * Evaluates an XPath expression on the given XML file.
 * Assumes that every result node is a text node.
 *
 * @param xml_data - the XML data as a string.
 * @param expression - the expressions to evaluate.
 * @param namespaces - a list of namespaces, containing two elements
 *   for every namespace: a prefix, and a href (in that order).
 * @return a wb_str_list containing the results. IMPORTANT: the
 *   returned list must be freed with wb_list_free().
 */
struct wb_str_list *
xpath_eval_expr(const char *xml_data, const char *expression,
	struct wb_str_list *namespaces) {

	struct wb_str_list *results = NULL;
	xmlDocPtr xml_doc;
	xmlXPathObjectPtr results_xpath_object;

	/* Create an XML document from XML data */
	xml_doc = xmlParseDoc(BAD_CAST xml_data);
	if (xml_doc == NULL) {
		return NULL;
	}

	/* Evaluate the XPath expression */
	results_xpath_object = libxml_xpath_eval_expr(xml_doc,
		BAD_CAST expression, namespaces);
	if (results_xpath_object == NULL) {
		xmlFreeDoc(xml_doc);
		return NULL;
	}

	/* Get the result list from the XML object */
	results = xpath_object_to_str_list(results_xpath_object, xml_doc);

	/* Cleanup */
	xmlXPathFreeObject(results_xpath_object);
	xmlFreeDoc(xml_doc);

	return results;
}
