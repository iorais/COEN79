

void insert(const value_type& entry) {
    new_head = node(entry, head);
    head = new_head;
}

void grab() {
    random = rand(0, list_length(head));
    node *p = head;
    for(int i = 0; i < random; i ++)
        p = p->next;

    return p->value;
}