/*
 * Copyright 2017, Cypress Semiconductor Corporation or a subsidiary of
 * Cypress Semiconductor Corporation. All Rights Reserved.
 *
 * This software, associated documentation and materials ("Software"),
 * is owned by Cypress Semiconductor Corporation
 * or one of its subsidiaries ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products. Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */

/** @file
 *
 */

#include "string.h"
#include "linked_list.h"

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Static Function Declarations
 ******************************************************/

/******************************************************
 *               Variable Definitions
 ******************************************************/

/******************************************************
 *               Function Definitions
 ******************************************************/

enum result_e linked_list_init( linked_list_t* list )
{
    if ( list == NULL )
    {
        return BAD_ARG;
    }

    memset( list, 0, sizeof( *list ) );
    return SUCCESS;
}

enum result_e linked_list_deinit( linked_list_t* list )
{
    linked_list_node_t* current;

    if ( list == NULL )
    {
        return BAD_ARG;
    }

    /* Traverse through all nodes and detach them */
    current = list->front;

    while ( current != NULL )
    {
        linked_list_node_t* next = current->next;

        /* Detach node from the list */
        current->prev = NULL;
        current->next = NULL;

        /* Move to the next node */
        current = next;
    }

    memset( list, 0, sizeof( *list ) );
    return SUCCESS;
}

enum result_e linked_list_get_count( linked_list_t* list, uint32_t* count )
{
    if ( list == NULL )
    {
        return BAD_ARG;
    }

    *count = list->count;

    return SUCCESS;
}

enum result_e linked_list_set_node_data( linked_list_node_t* node, const void* data )
{
    if ( node == NULL )
    {
        return BAD_ARG;
    }

    node->data = (void*)data;
    return SUCCESS;
}

enum result_e linked_list_get_front_node( linked_list_t* list, linked_list_node_t** front_node )
{
    if ( list == NULL )
    {
        return BAD_ARG;
    }

    if ( list->count == 0 )
    {
        *front_node = NULL;
        return NOT_FOUND;
    }

    *front_node = list->front;

    return SUCCESS;
}

enum result_e linked_list_get_rear_node( linked_list_t* list, linked_list_node_t** rear_node )
{
    if ( list == NULL )
    {
        return BAD_ARG;
    }

    if ( list->count == 0 )
    {
        *rear_node = NULL;
        return NOT_FOUND;
    }

    *rear_node = list->rear;

    return SUCCESS;
}

enum result_e linked_list_find_node( linked_list_t* list, linked_list_compare_callback_t callback, void* user_data, linked_list_node_t** node_found )
{
    linked_list_node_t* current;

    if ( list == NULL || callback == NULL || node_found == NULL || list->count == 0 )
    {
        return BAD_ARG;
    }

    current = list->front;

    while ( current != NULL )
    {
        if ( callback( current, user_data ) == true )
        {
            *node_found = current;
            return SUCCESS;
        }

        current = current->next;
    }

    return NOT_FOUND;
}

enum result_e linked_list_insert_node_at_front( linked_list_t* list, linked_list_node_t* node )
{
    if ( list == NULL || node == NULL )
    {
        return BAD_ARG;
    }

    if ( list->count == 0 )
    {
        list->front = node;
        list->rear  = node;
        node->prev  = NULL;
        node->next  = NULL;
    }
    else
    {
        node->prev        = NULL;
        node->next        = list->front;
        list->front->prev = node;
        list->front       = node;
    }

    list->count++;

    return SUCCESS;
}

enum result_e linked_list_insert_node_at_rear( linked_list_t* list, linked_list_node_t* node )
{
    if ( list == NULL || node == NULL )
    {
        return BAD_ARG;
    }

    if ( list->count == 0 )
    {
        list->front = node;
        list->rear  = node;
        node->prev  = NULL;
        node->next  = NULL;
    }
    else
    {
        node->next       = NULL;
        node->prev       = list->rear;
        list->rear->next = node;
        list->rear       = node;
    }

    list->count++;

    return SUCCESS;
}

enum result_e linked_list_insert_node_before( linked_list_t* list, linked_list_node_t* reference_node, linked_list_node_t* node_to_insert )
{
    /* WARNING: User must make sure that reference_node is in the list */
    if ( list == NULL || reference_node == NULL || node_to_insert == NULL || list->count == 0 )
    {
        return BAD_ARG;
    }

    if ( list->count == 0 )
    {
        return NOT_FOUND;
    }

    if ( reference_node == list->front )
    {
        return linked_list_insert_node_at_front( list, node_to_insert );
    }
    else
    {
        node_to_insert->prev       = reference_node->prev;
        node_to_insert->prev->next = node_to_insert;
        node_to_insert->next       = reference_node;
        reference_node->prev       = node_to_insert;

        list->count++;

        return SUCCESS;
    }
}

enum result_e linked_list_insert_node_after( linked_list_t* list, linked_list_node_t* reference_node, linked_list_node_t* node_to_insert )
{
    /* WARNING: User must make sure that reference_node is in the list */
    if ( list == NULL || reference_node == NULL || node_to_insert == NULL || list->count == 0 )
    {
        return BAD_ARG;
    }

    if ( reference_node == list->rear )
    {
        return linked_list_insert_node_at_rear( list, node_to_insert );
    }
    else
    {
        node_to_insert->prev       = reference_node;
        node_to_insert->next       = reference_node->next;
        reference_node->next->prev = node_to_insert;
        reference_node->next       = node_to_insert;

        list->count++;

        return SUCCESS;
    }
}

enum result_e linked_list_remove_node( linked_list_t* list, linked_list_node_t* node )
{
    /* WARNING: User must make sure that node to remove is in the list */
    if ( list == NULL || node == NULL )
    {
        return BAD_ARG;
    }

    if ( list->count == 0 )
    {
        return NOT_FOUND;
    }

    if ( list->count == 1 )
    {
        list->front = NULL;
        list->rear  = NULL;
    }
    else if ( node == list->front )
    {
        linked_list_node_t* removed_node;

        return linked_list_remove_node_from_front( list, &removed_node );
    }
    else if ( node == list->rear )
    {
        linked_list_node_t* removed_node;

        return linked_list_remove_node_from_rear( list, &removed_node );
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    /* Make sure that detach node does not point to some arbitrary memory location */
    node->prev = NULL;
    node->next = NULL;

    list->count--;

    return SUCCESS;
}

enum result_e linked_list_remove_node_from_front( linked_list_t* list, linked_list_node_t** removed_node )
{
    if ( list == NULL || removed_node == NULL || list->count == 0 )
    {
        return BAD_ARG;
    }

    *removed_node = list->front;

    if ( list->count == 1 )
    {
        list->front = NULL;
        list->rear  = NULL;
    }
    else
    {
        list->front       = list->front->next;
        list->front->prev = NULL;
    }

    /* Make sure node does not point to some arbitrary memory location */
    (*removed_node)->prev = NULL;
    (*removed_node)->next = NULL;

    list->count--;

    return SUCCESS;
}

enum result_e linked_list_remove_node_from_rear( linked_list_t* list, linked_list_node_t** removed_node )
{
    if ( list == NULL || removed_node == NULL )
    {
        return BAD_ARG;
    }

    if ( list->count == 0 )
    {
        return NOT_FOUND;
    }

    *removed_node = list->rear;

    if ( list->count == 1 )
    {
        list->front = NULL;
        list->rear  = NULL;
    }
    else
    {
        list->rear       = list->rear->prev;
        list->rear->next = NULL;
    }

    /* Make sure node does not point to some arbitrary memory location */
    (*removed_node)->prev = NULL;
    (*removed_node)->next = NULL;

    list->count--;

    return SUCCESS;
}
