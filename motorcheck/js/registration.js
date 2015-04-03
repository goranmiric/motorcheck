(function ($) {

  /**
  * Registration field validate.
  */
  Drupal.behaviors.motorcheckRegistration = {
    attach: function (context) {

      $('.motorcheck-reg-element input').blur(function () {
        var form = $(this).closest('form');
        var regNumber = $(this).val();
        var regex = /^\d{2,3}[-\s]?[A-Za-z]{1,2}[-\s]?(\d{1,6})$/;

        if ( regNumber ) {
          if ( regex.test(regNumber) ) {
            $('#motorcheck-registration-error').hide();
            // Validate registration
            validateRegistration(regNumber, form);
          } else {
            $('#motorcheck-registration-error').show();
          }
        } else {
          $('input.form-submit', form).attr('disabled', true);
          $('#motorcheck-registration-error, i.ajax-loader').hide();
        }

      });
    }
  };

  // Validate registration callback
  validateRegistration = function (registration, form) {
    // Add/Remove classes to/from ajax loader
    validateRegistrationLoaderClass('fa-progress');

    // Ajax call
    $.ajax({
      url: '/motorcheck/registration-validate',
      data: { reg: registration, dep: 4000 },
      async: true,
      type: 'get',
      dataType: 'json',
      success: function (response) {
        var result = JSON.parse(response);
        $('.motorcheck-reg-element textarea', form).val(response);

        if(result.errors) {
          $('#motorcheck-registration-error').show().html(result.errors[0].message);
          validateRegistrationLoaderClass('fa-error');

          $('input.form-submit', form).attr('disabled', true);
        }
        else {
          validateRegistrationLoaderClass('fa-success');
          $('input.form-submit', form).attr('disabled', false);
        }
      }
    });
  };

  // Add/Remove classes to/from ajax loader
  validateRegistrationLoaderClass = function (classValue) {
    var classes = ['fa-error', 'fa-success', 'fa-progress'];
    var element = $('i.ajax-loader');

    $(classes).each( function(k, val) {
      if( element.hasClass(val) ) {
        element.removeClass(val)
      }
    });
    element.addClass(classValue);
    element.show();
  };

})(jQuery);