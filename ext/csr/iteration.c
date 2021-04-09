VALUE csr_each(VALUE self) {
  csr_matrix* input;

  TypedData_Get_Struct(self, csr_matrix, &csr_data_type, input);

  for (size_t index = 0; index < input->count; index++) {
    rb_yield(DBL2NUM(input->elements[index]));
  }

  return self;
}

VALUE csr_each_row(VALUE self) {
  csr_matrix* input;

  TypedData_Get_Struct(self, csr_matrix, &csr_data_type, input);

  for (size_t i = 0; i < input->shape[0]; i++) {
    size_t row_len = input->ip[i + 1] - input->ip[i];
    VALUE* row_array = ALLOC_N(VALUE, row_len);

    for(size_t j = input->ip[i]; j < input->ip[i + 1]; j++) {
      row_array[j - input->ip[i]] = DBL2NUM(input->elements[j]);
    }

    rb_yield(rb_ary_new4(row_len, row_array));
  }

  return self;
}