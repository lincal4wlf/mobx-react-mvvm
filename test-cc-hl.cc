  void set_pxtr(std::vector<RFGoodsFooResponse*>* foo_responses,
                const ks::platform::CommonRecoResponse& response) const {
    for (int i = 0; i < response.item_size(); i++) {
      auto predict_item_feat = response.item(i);
      auto outRFGoodsFooResponse = (*foo_responses)[i];
      for (auto& attr : predict_item_feat.item_attr()) {
#define HANDLE_XTR(xtr)                                                                       \
  if (attr.name() == #xtr && !attr.float_list_value().empty()) {                              \
    ::ks::bar::Feature* rf_response_##xtr = outRFGoodsFooResponse->mutable_##xtr();         \
    rf_response_##xtr->Clear();                                                               \
    sample_attr2feature<foo::SampleAttr, foo::CommonSampleEnum>(attr, rf_response_##xtr); \
  }
        HANDLE_XTR(ctr);
        HANDLE_XTR(ltr);
        HANDLE_XTR(lvtr);
        HANDLE_XTR(str);
        HANDLE_XTR(wtr);
        HANDLE_XTR(cvr);
#undef HANDLE_XTR
      }
    }
  }
