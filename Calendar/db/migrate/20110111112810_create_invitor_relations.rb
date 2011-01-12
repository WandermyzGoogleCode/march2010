class CreateInvitorRelations < ActiveRecord::Migration
  def self.up
    create_table :invitor_relations do |t|
      t.integer :user_id
      t.integer :invitation_id

      t.timestamps
    end
  end

  def self.down
    drop_table :invitor_relations
  end
end
