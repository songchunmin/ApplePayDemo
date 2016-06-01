    Apply pay代码实现之前先配置证书和Merchant ID ；具体操作：http://blog.csdn.net/songchunmin_/article/details/51543356
    APPly pay 实现代码和注意事项：http://blog.csdn.net/songchunmin_/article/details/51549207

    /*  判定用户是否能够支付，在创建支付请求之前，要首先通过调用PKPaymentAuthorizationViewController 类里的
        canMakePaymentsUsingNetworks:方法来判断用户是否能够使用你提供的支付网络进行支付。
        如果要判断用户的硬件是否支持Apple Pay或者是否因为家长控制而不能支付，请使用canMakePayments 方法。
        如果用户不能进行支付，那就不要显示支付按钮，相应的应该退回到其它支付方式。
     */
    if([PKPaymentAuthorizationViewController canMakePayments]) {

        NSLog(@"Woo! Can make payments!");
        
        PKPaymentRequest *request = [[PKPaymentRequest alloc] init];

        PKPaymentSummaryItem *widget1 = [PKPaymentSummaryItem summaryItemWithLabel:@"娃哈哈"
                                                                            amount:[NSDecimalNumber decimalNumberWithString:@"0.01"]
                                                                              type:PKPaymentSummaryItemTypeFinal];
        
        PKPaymentSummaryItem *widget2 = [PKPaymentSummaryItem summaryItemWithLabel:@"鲜牛奶"
                                                                          amount:[NSDecimalNumber decimalNumberWithString:@"0.01"]];
        
        PKPaymentSummaryItem *total = [PKPaymentSummaryItem summaryItemWithLabel:@"Grand Total"
                                                                          amount:[NSDecimalNumber decimalNumberWithString:@"0.02"]];

        //数组中，最后的对象是总价。
        request.paymentSummaryItems = @[widget1, widget2, total];
        //国家--一定要填写正确，如果不知道的话，随便输入，控制台会列举所有的出来，
        request.countryCode = @"CN";
        //货币单位需要使用- 人民币
        request.currencyCode = @"CNY";
        //Wallet所绑定的卡的类型, 银联记得加上，我记得在配置证书那里选项，是否支持中国境内（大概意思），这里不加PKPaymentNetworkChinaUnionPay直接Crash，估计和这个有关。。。
        request.supportedNetworks = @[PKPaymentNetworkAmex, PKPaymentNetworkMasterCard, PKPaymentNetworkVisa,PKPaymentNetworkChinaUnionPay];
        request.merchantIdentifier = @"merchant.com.scm.PayDemo";
        //通过指定merchantCapabilities属性来指定你支持的支付处理标准，3DS支付方式是必须支持的，EMV方式是可选的。
        request.merchantCapabilities = PKMerchantCapabilityEMV;
        
        //设置后，如果用户之前没有填写过，那么会要求用户必须填写才能够使用Apple Pay
        //request.requiredShippingAddressFields = PKAddressFieldPostalAddress | PKAddressFieldPhone | PKAddressFieldEmail | PKAddressFieldName;

        //显示支付信息的控制器
        self.paymentPane = [[PKPaymentAuthorizationViewController alloc] initWithPaymentRequest:request];
        self.paymentPane.delegate = self;
        [self presentViewController:_paymentPane animated:TRUE completion:nil];

        
    } else {
        NSLog(@"This device cannot make payments");
    }
