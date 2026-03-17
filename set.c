FUNCTION set_add(set, id):
    // 1. Basic error control
    IF set IS NULL OR id IS EQUAL TO NO_ID THEN
        RETURN ERROR
    END IF

    // 2. Check if the set is full
    IF set->n_ids IS GREATER THAN OR EQUAL TO MAX_IDS THEN
        RETURN ERROR
    END IF

    // 3. Check if the element already exists (no duplicates allowed)
    FOR i FROM 0 TO set->n_ids - 1 DO
        IF set->ids[i] IS EQUAL TO id THEN
            // The element is already in the set, do nothing
            RETURN OK 
        END IF
    END FOR

    // 4. If it doesn't exist and there is space, add it at the end
    set->ids[set->n_ids] = id

    // 5. Increment the element counter
    set->n_ids = set->n_ids + 1

    RETURN OK
END FUNCTION

FUNCTION set_del(set, id):
    // 1. Basic error control and empty set
    IF set IS NULL OR id IS EQUAL TO NO_ID OR set->n_ids IS EQUAL TO 0 THEN
        RETURN ERROR
    END IF

    // 2. Search for the element to delete
    FOR i FROM 0 TO set->n_ids - 1 DO
        IF set->ids[i] IS EQUAL TO id THEN
            
            // 3. Element found. 
            // To efficiently cover the gap, we copy the last element
            // of the array into the current position 'i' (order doesn't matter).
            set->ids[i] = set->ids[set->n_ids - 1]
            
            // Clear the last position (optional, but good practice)
            set->ids[set->n_ids - 1] = NO_ID

            // 4. Reduce the element counter
            set->n_ids = set->n_ids - 1

            RETURN OK
        END IF
    END FOR

    // 5. If the loop ends and OK has not been returned, the element was not there
    RETURN ERROR
END FUNCTION