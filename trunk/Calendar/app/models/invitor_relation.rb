# Table schema: (invitation_id: integer, user_id: integer)
class InvitorRelation < ActiveRecord::Base
  belongs_to :invitation
  belongs_to :user
end
